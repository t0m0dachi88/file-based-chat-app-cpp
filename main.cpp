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

using namespace std;

// --- Utility Functions ---

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Forgot Password" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: ";
}

void displayDashboard() {
    cout << "\n===== DASHBOARD =====" << endl;
    cout << "1. Private Chat" << endl;
    cout << "2. Search Messages" << endl;
    cout << "3. Profile" << endl;
    cout << "4. Logout" << endl;
    cout << "Choose an option: ";
}

void displayPrivateChatMenu() {
    cout << "\n===== PRIVATE CHAT =====" << endl;
    cout << "1. Send Message" << endl;
    cout << "2. View Chat History" << endl;
    cout << "3. Back" << endl;
    cout << "Choose an option: ";
}

void displayAdminMenu() {
    cout << "\n===== ADMIN MENU =====" << endl;
    cout << "1. Remove User" << endl;
    cout << "2. View All Users" << endl;
    cout << "3. Logout" << endl;
    cout << "Choose an option: ";
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
            displayMainMenu();
            int choice;
            if (!(cin >> choice)) {
                clearInput();
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }
            clearInput();

            if (choice == 1) { // Register
                string username, password, type, question, answer;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                cout << "Enter type (admin/member): ";
                getline(cin, type);

                if (username.empty() || password.empty()) {
                    cout << "Error: Username and password cannot be empty." << endl;
                    continue;
                }

                // Check for duplicate username using algorithm
                auto it = find_if(users.begin(), users.end(), 
                    [&](const unique_ptr<User>& u) { return u->getUsername() == username; });
                if (it != users.end()) {
                    cout << "Error: Username already exists! Please choose another." << endl;
                    continue;
                }

                // Security question setup
                cout << "\n--- Security Question Setup ---" << endl;
                cout << "Set a security question (e.g. What is your pet's name?): ";
                getline(cin, question);
                cout << "Set the answer: ";
                getline(cin, answer);

                if (question.empty() || answer.empty()) {
                    cout << "Error: Security question and answer cannot be empty." << endl;
                    continue;
                }

                try {
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
                    cout << "Registration successful! You may now log in." << endl;
                } catch (const exception& e) {
                    cout << "Registration failed: " << e.what() << endl;
                }

            } else if (choice == 2) { // Login
                string username, password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                
                bool found = false;
                for (const auto& u : users) {
                    if (u->getUsername() == username) {
                        found = true;
                        if (u->login(password)) {
                            currentUser = u.get();
                            // Demonstrating type conversion operator
                            logger.log("User logged in: " + string(*currentUser));
                            cout << "Login successful! Welcome, " << currentUser->getUsername() << "." << endl;
                        } else {
                            cout << "Error: Invalid password!" << endl;
                        }
                        break;
                    }
                }
                if (!found) {
                    cout << "Error: User not found!" << endl;
                }

            } else if (choice == 3) { // Forgot Password
                string username;
                cout << "Enter your username: ";
                getline(cin, username);
                
                User* targetUser = nullptr;
                for (const auto& u : users) {
                    if (u->getUsername() == username) { 
                        targetUser = u.get(); 
                        break; 
                    }
                }
                
                if (!targetUser) {
                    cout << "Error: User not found!" << endl;
                } else if (targetUser->getSecurityQuestion().empty()) {
                    cout << "Error: No security question set for this account." << endl;
                } else {
                    cout << "Security Question: " << targetUser->getSecurityQuestion() << endl;
                    cout << "Your Answer: ";
                    string answer;
                    getline(cin, answer);
                    
                    if (targetUser->checkSecurityAnswer(answer)) {
                        string newPass, confirmPass;
                        cout << "Answer correct! Enter new password: ";
                        getline(cin, newPass);
                        cout << "Confirm new password: ";
                        getline(cin, confirmPass);
                        
                        if (newPass.empty()) {
                            cout << "Error: Password cannot be empty." << endl;
                        } else if (newPass != confirmPass) {
                            cout << "Error: Passwords do not match!" << endl;
                        } else {
                            try {
                                targetUser->setPassword(newPass);
                                fm.saveUsers(users);
                                logger.log("Password reset successful for: " + username);
                                cout << "Password reset successful! You can now log in." << endl;
                            } catch (const exception& e) {
                                cout << "Failed to reset password: " << e.what() << endl;
                            }
                        }
                    } else {
                        cout << "Error: Incorrect answer! Password reset denied." << endl;
                    }
                }

            } else if (choice == 4) { // Exit
                break;
            } else {
                cout << "Invalid choice! Please select an option from the menu." << endl;
            }
        } else {
            // --- Logged In Session ---
            
            if (currentUser->canModerate()) {
                displayAdminMenu();
                int choice;
                if (!(cin >> choice)) {
                    clearInput();
                    cout << "Invalid input! Please enter a number." << endl;
                    continue;
                }
                clearInput();

                if (choice == 1) { // Remove User
                    string username;
                    cout << "Enter username to remove: ";
                    getline(cin, username);
                    
                    if (username == currentUser->getUsername()) {
                        cout << "Error: You cannot remove yourself." << endl;
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
                        cout << "User removed successfully!" << endl;
                    } else {
                        cout << "Error: User not found!" << endl;
                    }

                } else if (choice == 2) { // View All Users
                    cout << "\n--- All Registered Users ---" << endl;
                    if (users.empty()) cout << "No users found." << endl;
                    for (const auto& u : users) {
                        cout << *u << endl;
                    }

                } else if (choice == 3) { // Logout
                    currentUser->logout();
                    currentUser = nullptr;
                    logger.log("Admin logged out.");
                    cout << "Logged out successfully." << endl;

                } else {
                    cout << "Invalid choice!" << endl;
                }
                
            } else {
                displayDashboard();
                int choice;
                if (!(cin >> choice)) {
                    clearInput();
                    cout << "Invalid input! Please enter a number." << endl;
                    continue;
                }
                clearInput();

                if (choice == 1) { // Private Chat
                    string recipient;
                    cout << "Enter recipient username: ";
                    getline(cin, recipient);
                    
                    if (recipient == currentUser->getUsername()) {
                        cout << "Error: You cannot chat with yourself." << endl;
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
                        cout << "Error: User not found!" << endl;
                        continue;
                    }

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
                        displayPrivateChatMenu();
                        int pchoice;
                        if (!(cin >> pchoice)) {
                            clearInput();
                            cout << "Invalid input! Please enter a number." << endl;
                            continue;
                        }
                        clearInput();

                        if (pchoice == 1) { // Send Message
                            string content;
                            cout << "Enter message: ";
                            getline(cin, content);
                            try {
                                if (content.empty()) {
                                    throw invalid_argument("Message content cannot be empty.");
                                }
                                auto msg = make_unique<EncryptedMessage>(currentUser->getUsername(), content);
                                chat->addMessage(move(msg));
                                fm.savePrivateChat(chat);
                                logger.log("Message sent in private chat: " + chatId);
                                cout << "Message sent." << endl;
                            } catch (const exception& e) {
                                cout << "Error: " << e.what() << endl;
                            }

                        } else if (pchoice == 2) { // View History
                            cout << "\n--- Chat History ---" << endl;
                            chat->viewHistory();
                            chat->markAsRead(); // Mark as read explicitly after viewing
                            fm.savePrivateChat(chat); // Save state

                        } else if (pchoice == 3) { // Back
                            break;
                        } else {
                            cout << "Invalid choice!" << endl;
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
                    cout << "Enter keyword to search: ";
                    getline(cin, keyword);
                    cout << "Enter sender username to filter by (or leave blank to search all): ";
                    getline(cin, searchSender);

                    if (keyword.empty()) {
                        cout << "Error: Keyword cannot be empty." << endl;
                        continue;
                    }

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

                    cout << "\n--- Search Results (" << results.size() << ") ---" << endl;
                    if (results.empty()) {
                        cout << "No messages found matching your criteria." << endl;
                    } else {
                        for (const auto* msg : results) {
                            msg->display();
                        }
                    }

                } else if (choice == 3) { // Profile
                    cout << "\n--- Profile Information ---" << endl;
                    currentUser->displayProfile();

                } else if (choice == 4) { // Logout
                    currentUser->logout();
                    currentUser = nullptr;
                    logger.log("User logged out.");
                    cout << "Logged out successfully." << endl;

                } else {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
    }

    // No manual memory cleanup required! std::unique_ptr handles all dynamic memory safely.
    logger.log("Application exited normally.");
    cout << "Thank you for using Kilo Chat App. Goodbye!" << endl;
    
    return 0;
}