#include "User.h"
#include "Admin.h"
#include "Member.h"
#include "Message.h"
#include "TextMessage.h"
#include "EncryptedMessage.h"
#include "PrivateChat.h"
#include "FileManager.h"
#include "EncryptionManager.h"
#include "SearchEngine.h"
#include "Logger.h"

#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <thread>
#include <chrono>

using namespace std;

// --- Utility Functions ---

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clearScreen() {
    system("cls");
}

void printHeader(const string& title) {
    cout << "\033[1;34m"; // Blue
    cout << "==============================" << endl;
    int spaces = (30 - title.length()) / 2;
    if (spaces < 0) spaces = 0;
    cout << string(spaces, ' ') << title << endl;
    cout << "==============================\033[0m\n" << endl;
}

void printMenu(const vector<string>& options) {
    for (size_t i = 0; i < options.size(); ++i) {
        cout << "[" << i + 1 << "] " << options[i] << endl;
    }
    cout << "\n\033[1;34m------------------------------\033[0m" << endl;
    cout << "> Enter your choice: ";
}

void printSuccess(const string& msg) {
    cout << "\033[1;32m" << msg << "\033[0m" << endl;
    this_thread::sleep_for(chrono::milliseconds(1500));
}

void printError(const string& msg) {
    cout << "\033[1;31m" << msg << "\033[0m" << endl;
    this_thread::sleep_for(chrono::milliseconds(1500));
}

void loadingAnimation() {
    cout << "\033[1;33mLoading";
    for (int i = 0; i < 3; ++i) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    cout << "\033[0m\n" << endl;
}

// --- Main Application Logic ---

int main() {
    // Note: Directory creation is now safely handled inside FileManager constructor
    FileManager fm;
    SearchEngine se;
    Logger<string> logger("app");
    
    // Core state uses std::unique_ptr for memory safety
    vector<unique_ptr<User>> users = fm.loadUsers();
    unordered_map<string, unique_ptr<PrivateChat>> privateChats;
    
    // Raw pointer for observing (not owning) the current session
    User* currentUser = nullptr;

    logger.log("Application started successfully.");

    while (true) {
        if (!currentUser) {
            clearScreen();
            printHeader("CHAT APPLICATION");
            printMenu({"Register", "Login", "Forgot Password", "Exit"});
            int choice;
            if (!(cin >> choice)) {
                clearInput();
                printError("Invalid input! Please enter a number.");
                continue;
            }
            clearInput();

            if (choice == 1) { // Register
                string username, password, type, question, answer;
                cout << "> Enter Username: ";
                getline(cin, username);
                cout << "> Enter Password: ";
                getline(cin, password);
                cout << "> Enter Type (admin/member): ";
                getline(cin, type);

                if (username.empty() || password.empty()) {
                    printError("Error: Username and password cannot be empty.");
                    continue;
                }

                // Check for duplicate username using algorithm
                auto it = find_if(users.begin(), users.end(), 
                    [&](const unique_ptr<User>& u) { return u->getUsername() == username; });
                if (it != users.end()) {
                    printError("Error: Username already exists! Please choose another.");
                    continue;
                }

                // Security question setup
                cout << "\n\033[1;34m--- Security Question Setup ---\033[0m" << endl;
                cout << "> Set a security question (e.g. What is your pet's name?): ";
                getline(cin, question);
                cout << "> Set the answer: ";
                getline(cin, answer);

                if (question.empty() || answer.empty()) {
                    printError("Error: Security question and answer cannot be empty.");
                    continue;
                }

                try {
                    loadingAnimation();
                    unique_ptr<User> newUser;
                    if (type == "admin" || type == "Admin") {
                        newUser = make_unique<Admin>(username, password);
                    } else {
                        newUser = make_unique<Member>(username, password); // Default to member
                    }
                    newUser->setSecurityQuestion(question);
                    newUser->setSecurityAnswer(answer);
                    
                    users.push_back(move(newUser));
                    fm.saveUsers(users);
                    
                    logger.log("User registered successfully: " + username);
                    printSuccess("Registration successful! You may now log in.");
                } catch (const exception& e) {
                    printError("Registration failed: " + string(e.what()));
                }

            } else if (choice == 2) { // Login
                string username, password;
                cout << "> Enter Username: ";
                getline(cin, username);
                cout << "> Enter Password: ";
                getline(cin, password);
                
                loadingAnimation();
                
                bool found = false;
                for (const auto& u : users) {
                    if (u->getUsername() == username) {
                        found = true;
                        if (u->login(password)) {
                            currentUser = u.get();
                            // Demonstrating type conversion operator
                            logger.log("User logged in: " + string(*currentUser));
                            printSuccess("Login successful! Welcome, " + currentUser->getUsername() + ".");
                        } else {
                            printError("Error: Invalid password!");
                        }
                        break;
                    }
                }
                if (!found) {
                    printError("Error: User not found!");
                }

            } else if (choice == 3) { // Forgot Password
                string username;
                cout << "> Enter your username: ";
                getline(cin, username);
                
                User* targetUser = nullptr;
                for (const auto& u : users) {
                    if (u->getUsername() == username) { 
                        targetUser = u.get(); 
                        break; 
                    }
                }
                
                if (!targetUser) {
                    printError("Error: User not found!");
                } else if (targetUser->getSecurityQuestion().empty()) {
                    printError("Error: No security question set for this account.");
                } else {
                    cout << "\033[1;33mSecurity Question: \033[0m" << targetUser->getSecurityQuestion() << endl;
                    cout << "> Your Answer: ";
                    string answer;
                    getline(cin, answer);
                    
                    if (targetUser->checkSecurityAnswer(answer)) {
                        string newPass, confirmPass;
                        cout << "> Answer correct! Enter new password: ";
                        getline(cin, newPass);
                        cout << "> Confirm new password: ";
                        getline(cin, confirmPass);
                        
                        if (newPass.empty()) {
                            printError("Error: Password cannot be empty.");
                        } else if (newPass != confirmPass) {
                            printError("Error: Passwords do not match!");
                        } else {
                            try {
                                loadingAnimation();
                                targetUser->setPassword(newPass);
                                fm.saveUsers(users);
                                logger.log("Password reset successful for: " + username);
                                printSuccess("Password reset successful! You can now log in.");
                            } catch (const exception& e) {
                                printError("Failed to reset password: " + string(e.what()));
                            }
                        }
                    } else {
                        printError("Error: Incorrect answer! Password reset denied.");
                    }
                }

            } else if (choice == 4) { // Exit
                break;
            } else {
                printError("Invalid choice! Please select an option from the menu.");
            }
        } else {
            // --- Logged In Session ---
            
            if (currentUser->canModerate()) {
                clearScreen();
                printHeader("ADMIN MENU");
                printMenu({"Remove User", "Unlock User", "View All Users", "Logout"});
                int choice;
                if (!(cin >> choice)) {
                    clearInput();
                    printError("Invalid input! Please enter a number.");
                    continue;
                }
                clearInput();

                if (choice == 1) { // Remove User
                    string username;
                    cout << "> Enter username to remove: ";
                    getline(cin, username);
                    
                    if (username == currentUser->getUsername()) {
                        printError("Error: You cannot remove yourself.");
                        continue;
                    }

                    auto it = find_if(users.begin(), users.end(), 
                        [&](const unique_ptr<User>& u){ return u->getUsername() == username; });
                        
                    if (it != users.end()) {
                        string targetUser = (*it)->getUsername();
                        users.erase(it); // unique_ptr automatically cleans up memory
                        fm.saveUsers(users);
                        
                        // Clean up associated private chats
                        auto chatIt = privateChats.begin();
                        while (chatIt != privateChats.end()) {
                            if (chatIt->second->getUser1() == targetUser || chatIt->second->getUser2() == targetUser) {
                                fm.deletePrivateChatFile(chatIt->second->getId());
                                chatIt = privateChats.erase(chatIt);
                            } else {
                                ++chatIt;
                            }
                        }

                        logger.log("Admin removed user: " + username);
                        printSuccess("User removed successfully!");
                    } else {
                        printError("Error: User not found!");
                    }

                } else if (choice == 2) { // Unlock User
                    string username;
                    cout << "> Enter username to unlock: ";
                    getline(cin, username);
                    
                    auto it = find_if(users.begin(), users.end(), 
                        [&](const unique_ptr<User>& u){ return u->getUsername() == username; });
                        
                    if (it != users.end()) {
                        loadingAnimation();
                        (*it)->unlock();
                        printSuccess("User '" + username + "' has been unlocked.");
                        logger.log("Admin unlocked user: " + username);
                    } else {
                        printError("Error: User not found!");
                    }

                } else if (choice == 3) { // View All Users
                    clearScreen();
                    printHeader("ALL REGISTERED USERS");
                    if (users.empty()) cout << "No users found." << endl;
                    for (const auto& u : users) {
                        cout << *u << endl;
                    }
                    cout << "\n\033[1;33mPress Enter to go back...\033[0m";
                    string dummy;
                    getline(cin, dummy);

                } else if (choice == 4) { // Logout
                    currentUser->logout();
                    currentUser = nullptr;
                    logger.log("Admin logged out.");
                    printSuccess("Logged out successfully.");

                } else {
                    printError("Invalid choice!");
                }
                
            } else {
                clearScreen();
                printHeader("DASHBOARD");
                printMenu({"Private Chat", "Search Messages", "Profile", "Logout"});
                int choice;
                if (!(cin >> choice)) {
                    clearInput();
                    printError("Invalid input! Please enter a number.");
                    continue;
                }
                clearInput();

                if (choice == 1) { // Private Chat
                    string recipient;
                    cout << "> Enter recipient username: ";
                    getline(cin, recipient);
                    
                    if (recipient == currentUser->getUsername()) {
                        printError("Error: You cannot chat with yourself.");
                        continue;
                    }

                    User* recUser = nullptr;
                    for (const auto& u : users) {
                        if (u->getUsername() == recipient) {
                            recUser = u.get();
                            break;
                        }
                    }
                    if (!recUser) {
                        printError("Error: User not found!");
                        continue;
                    }
                    
                    loadingAnimation();

                    string u1 = currentUser->getUsername();
                    string u2 = recipient;
                    if (u1 > u2) swap(u1, u2);
                    string chatId = u1 + "_" + u2;

                    // Lazy load chat if not in memory
                    if (privateChats.find(chatId) == privateChats.end()) {
                        if (fm.privateChatExists(chatId)) {
                            auto loadedChat = fm.loadPrivateChat(chatId);
                            if (loadedChat) {
                                privateChats[chatId] = move(loadedChat);
                            } else {
                                privateChats[chatId] = make_unique<PrivateChat>(currentUser->getUsername(), recUser->getUsername());
                            }
                        } else {
                            privateChats[chatId] = make_unique<PrivateChat>(currentUser->getUsername(), recUser->getUsername());
                        }
                    }
                    
                    PrivateChat* chat = privateChats[chatId].get();

                    while (true) {
                        clearScreen();
                        printHeader("CHAT: " + recipient);
                        printMenu({"Send Message", "View Chat History", "Back"});
                        int pchoice;
                        if (!(cin >> pchoice)) {
                            clearInput();
                            printError("Invalid input! Please enter a number.");
                            continue;
                        }
                        clearInput();

                        if (pchoice == 1) { // Send Message
                            string content;
                            cout << "> Enter message: ";
                            getline(cin, content);
                            try {
                                if (content.empty()) {
                                    throw invalid_argument("Message content cannot be empty.");
                                }
                                loadingAnimation();
                                auto msg = make_unique<EncryptedMessage>(currentUser->getUsername(), content);
                                chat->addMessage(move(msg));
                                fm.savePrivateChat(chat);
                                logger.log("Message sent in private chat: " + chatId);
                                printSuccess("Message sent.");
                            } catch (const exception& e) {
                                printError("Error: " + string(e.what()));
                            }

                        } else if (pchoice == 2) { // View History
                            clearScreen();
                            printHeader("CHAT HISTORY");
                            chat->viewHistory();
                            chat->markAsRead(); // Mark as read explicitly after viewing
                            fm.savePrivateChat(chat); // Save state
                            cout << "\n\033[1;33mPress Enter to go back...\033[0m";
                            string dummy;
                            getline(cin, dummy);

                        } else if (pchoice == 3) { // Back
                            break;
                        } else {
                            printError("Invalid choice!");
                        }
                    }

                } else if (choice == 2) { // Search Messages
                    // Pre-load all relevant chats before searching
                    vector<string> chatIds = fm.getAllChatIdsForUser(currentUser->getUsername());
                    for (const string& chatId : chatIds) {
                        if (privateChats.find(chatId) == privateChats.end()) {
                            auto loadedChat = fm.loadPrivateChat(chatId);
                            if (loadedChat) {
                                privateChats[chatId] = move(loadedChat);
                            }
                        }
                    }

                    string keyword, searchSender;
                    cout << "> Enter keyword to search: ";
                    getline(cin, keyword);
                    cout << "> Enter sender username to filter by (or leave blank to search all): ";
                    getline(cin, searchSender);

                    if (keyword.empty()) {
                        printError("Error: Keyword cannot be empty.");
                        continue;
                    }
                    
                    loadingAnimation();

                    vector<const Message*> results;
                    for (const auto& pc : privateChats) {
                        // Only search in chats where the current user is a participant
                        if (pc.second->getUser1() == currentUser->getUsername() || pc.second->getUser2() == currentUser->getUsername()) {
                            vector<const Message*> res;
                            if (searchSender.empty()) {
                                res = se.search(pc.second->getMessages(), keyword);
                            } else {
                                res = se.search(pc.second->getMessages(), keyword, searchSender);
                            }
                            results.insert(results.end(), res.begin(), res.end());
                        }
                    }

                    clearScreen();
                    printHeader("SEARCH RESULTS (" + to_string(results.size()) + ")");
                    if (results.empty()) {
                        cout << "No messages found matching your criteria." << endl;
                    } else {
                        for (const auto* msg : results) {
                            msg->display();
                        }
                    }
                    cout << "\n\033[1;33mPress Enter to go back...\033[0m";
                    string dummy;
                    getline(cin, dummy);

                } else if (choice == 3) { // Profile
                    clearScreen();
                    printHeader("PROFILE INFORMATION");
                    currentUser->displayProfile();
                    cout << "\n\033[1;33mPress Enter to go back...\033[0m";
                    string dummy;
                    getline(cin, dummy);

                } else if (choice == 4) { // Logout
                    currentUser->logout();
                    currentUser = nullptr;
                    logger.log("User logged out.");
                    printSuccess("Logged out successfully.");

                } else {
                    printError("Invalid choice!");
                }
            }
        }
    }

    // No manual memory cleanup required! std::unique_ptr handles all dynamic memory safely.
    logger.log("Application exited normally.");
    printSuccess("Thank you for using Kilo Chat App. Goodbye!");
    
    return 0;
}