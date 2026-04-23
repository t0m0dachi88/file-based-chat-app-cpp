#include "User.h"
#include "Admin.h"
#include "Member.h"
#include "Message.h"
#include "TextMessage.h"
#include "EncryptedMessage.h"
#include "PrivateChat.h"
#include "ChatRoom.h"
#include "FileManager.h"
#include "EncryptionManager.h"
#include "SearchEngine.h"
#include "NotificationManager.h"
#include "Logger.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <cstdlib>

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Choose an option: ";
}

void displayDashboard() {
    cout << "\n===== DASHBOARD =====" << endl;
    cout << "1. Private Chat" << endl;
    cout << "2. Group Chat" << endl;
    cout << "3. Search Messages" << endl;
    cout << "4. Notifications" << endl;
    cout << "5. Profile" << endl;
    cout << "6. Logout" << endl;
    cout << "Choose an option: ";
}

void displayPrivateChatMenu() {
    cout << "\n===== PRIVATE CHAT =====" << endl;
    cout << "1. Send Message" << endl;
    cout << "2. View Chat History" << endl;
    cout << "3. Back" << endl;
    cout << "Choose an option: ";
}

void displayGroupChatMenu() {
    cout << "\n===== GROUP CHAT =====" << endl;
    cout << "1. Create Room" << endl;
    cout << "2. Join Room" << endl;
    cout << "3. Send Message" << endl;
    cout << "4. View Room Chat" << endl;
    cout << "5. Back" << endl;
    cout << "Choose an option: ";
}

void displayAdminMenu() {
    cout << "\n===== ADMIN MENU =====" << endl;
    cout << "1. Create Room" << endl;
    cout << "2. Delete Room" << endl;
    cout << "3. Remove User" << endl;
    cout << "4. View All Users" << endl;
    cout << "5. Logout" << endl;
    cout << "Choose an option: ";
}

int main() {
    // Create necessary directories
    system("mkdir data\\private_chats 2>nul");
    system("mkdir data\\room_chats 2>nul");
    system("mkdir data\\logs 2>nul");

    vector<User*> users;
    map<string, PrivateChat*> privateChats;
    map<string, ChatRoom*> chatRooms;
    FileManager fm;
    NotificationManager nm;
    SearchEngine se;
    EncryptionManager em;
    Logger<string> logger("app");
    User* currentUser = nullptr;

    // Load existing users
    users = fm.loadUsers();

    // Load existing rooms (simplified, assume some exist or create)
    // For demo, create a default room if none
    if (chatRooms.empty()) {
        Admin* defaultAdmin = nullptr;
        for (auto u : users) {
            if (dynamic_cast<Admin*>(u)) {
                defaultAdmin = dynamic_cast<Admin*>(u);
                break;
            }
        }
        if (!defaultAdmin) {
            defaultAdmin = new Admin("admin", "pass", "admin@chat.com");
            users.push_back(defaultAdmin);
        }
        ChatRoom* defaultRoom = new ChatRoom("General", defaultAdmin);
        chatRooms["General"] = defaultRoom;
    }

    logger.log("Application started");

    while (true) {
        if (!currentUser) {
            displayMainMenu();
            int choice;
            cin >> choice;
            clearInput();

            if (choice == 1) { // Register
                string username, password, email, type;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                cout << "Enter email: ";
                getline(cin, email);
                cout << "Enter type (admin/member): ";
                getline(cin, type);

                User* newUser = nullptr;
                if (type == "admin") {
                    newUser = new Admin(username, password, email);
                } else {
                    newUser = new Member(username, password, email);
                }
                users.push_back(newUser);
                fm.saveUsers(users);
                logger.log("User registered: " + username);
                cout << "Registration successful!" << endl;

            } else if (choice == 2) { // Login
                string username, password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                bool found = false;
                for (auto u : users) {
                    if (u->getUsername() == username) {
                        if (u->login(password)) {
                            currentUser = u;
                            logger.log("User logged in: " + username);
                            cout << "Login successful!" << endl;
                            found = true;
                        } else {
                            cout << "Invalid password!" << endl;
                        }
                        break;
                    }
                }
                if (!found) {
                    cout << "User not found!" << endl;
                }

            } else if (choice == 3) { // Exit
                break;
            } else {
                cout << "Invalid choice!" << endl;
            }
        } else {
            // Dashboard or Admin menu
            if (currentUser->canModerate()) {
                displayAdminMenu();
                int choice;
                cin >> choice;
                clearInput();

                if (choice == 1) { // Create Room
                    string roomName;
                    cout << "Enter room name: ";
                    getline(cin, roomName);
                    ChatRoom* newRoom = new ChatRoom(roomName, dynamic_cast<Admin*>(currentUser));
                    chatRooms[roomName] = newRoom;
                    fm.saveChatRoom(newRoom);
                    logger.log("Room created: " + roomName);
                    cout << "Room created!" << endl;

                } else if (choice == 2) { // Delete Room
                    string roomName;
                    cout << "Enter room name to delete: ";
                    getline(cin, roomName);
                    if (chatRooms.find(roomName) != chatRooms.end()) {
                        delete chatRooms[roomName];
                        chatRooms.erase(roomName);
                        logger.log("Room deleted: " + roomName);
                        cout << "Room deleted!" << endl;
                    } else {
                        cout << "Room not found!" << endl;
                    }

                } else if (choice == 3) { // Remove User
                    string username;
                    cout << "Enter username to remove: ";
                    getline(cin, username);
                    auto it = find_if(users.begin(), users.end(), [&](User* u){ return u->getUsername() == username; });
                    if (it != users.end()) {
                        delete *it;
                        users.erase(it);
                        fm.saveUsers(users);
                        logger.log("User removed: " + username);
                        cout << "User removed!" << endl;
                    } else {
                        cout << "User not found!" << endl;
                    }

                } else if (choice == 4) { // View All Users
                    cout << "All Users:" << endl;
                    for (auto u : users) {
                        cout << *u << endl;
                    }

                } else if (choice == 5) { // Logout
                    currentUser->logout();
                    currentUser = nullptr;
                    logger.log("Admin logged out");

                } else {
                    cout << "Invalid choice!" << endl;
                }
            } else {
                displayDashboard();
                int choice;
                cin >> choice;
                clearInput();

                if (choice == 1) { // Private Chat
                    string recipient;
                    cout << "Enter recipient username: ";
                    getline(cin, recipient);

                    User* recUser = nullptr;
                    for (auto u : users) {
                        if (u->getUsername() == recipient) {
                            recUser = u;
                            break;
                        }
                    }
                    if (!recUser) {
                        cout << "User not found!" << endl;
                        continue;
                    }

                    string u1 = currentUser->getUsername();
                    string u2 = recipient;
                    if (u1 > u2) swap(u1, u2);
                    string chatId = u1 + "_" + u2;

                    if (privateChats.find(chatId) == privateChats.end()) {
                        if (fm.privateChatExists(chatId)) {
                            privateChats[chatId] = fm.loadPrivateChat(chatId, users);
                        } else {
                            privateChats[chatId] = new PrivateChat(currentUser, recUser);
                        }
                    }
                    PrivateChat* chat = privateChats[chatId];

                    while (true) {
                        displayPrivateChatMenu();
                        int pchoice;
                        cin >> pchoice;
                        clearInput();

                        if (pchoice == 1) { // Send Message
                            string content;
                            cout << "Enter message: ";
                            getline(cin, content);
                            Message* msg = new EncryptedMessage(currentUser->getUsername(), content);
                            chat->sendMessage(msg);
                            fm.savePrivateChat(chat);
                            logger.log("Message sent in private chat");

                        } else if (pchoice == 2) { // View History
                            chat->viewHistory();

                        } else if (pchoice == 3) { // Back
                            break;
                        } else {
                            cout << "Invalid choice!" << endl;
                        }
                    }

                } else if (choice == 2) { // Group Chat
                    string roomName;
                    cout << "Enter room name: ";
                    getline(cin, roomName);

                    if (chatRooms.find(roomName) == chatRooms.end()) {
                        cout << "Room not found!" << endl;
                        continue;
                    }
                    ChatRoom* room = chatRooms[roomName];

                    while (true) {
                        displayGroupChatMenu();
                        int gchoice;
                        cin >> gchoice;
                        clearInput();

                        if (gchoice == 1) { // Create Room - but only admin
                            cout << "Only admin can create rooms!" << endl;

                        } else if (gchoice == 2) { // Join Room
                            room->addMember(currentUser);
                            cout << "Joined room!" << endl;

                        } else if (gchoice == 3) { // Send Message
                            string content;
                            cout << "Enter message: ";
                            getline(cin, content);
                            Message* msg = new TextMessage(currentUser->getUsername(), content);
                            room->sendMessage(msg);
                            fm.saveChatRoom(room);
                            logger.log("Message sent in group chat");

                        } else if (gchoice == 4) { // View Room Chat
                            room->viewHistory();

                        } else if (gchoice == 5) { // Back
                            break;
                        } else {
                            cout << "Invalid choice!" << endl;
                        }
                    }

                } else if (choice == 3) { // Search Messages
                    string keyword;
                    cout << "Enter keyword to search: ";
                    getline(cin, keyword);

                    // Search in all private chats and rooms
                    vector<Message*> results;
                    for (auto& pc : privateChats) {
                        auto res = se.searchByKeyword(pc.second->getMessages(), keyword);
                        results.insert(results.end(), res.begin(), res.end());
                    }
                    for (auto& cr : chatRooms) {
                        auto res = se.searchByKeyword(cr.second->getMessages(), keyword);
                        results.insert(results.end(), res.begin(), res.end());
                    }

                    cout << "Search results (" << results.size() << "):" << endl;
                    for (auto msg : results) {
                        msg->display();
                    }

                } else if (choice == 4) { // Notifications
                    nm.displayNotifications();

                } else if (choice == 5) { // Profile
                    currentUser->displayProfile();

                } else if (choice == 6) { // Logout
                    currentUser->logout();
                    currentUser = nullptr;
                    logger.log("User logged out");

                } else {
                    cout << "Invalid choice!" << endl;
                }
            }
        }
    }

    // Cleanup
    for (auto u : users) {
        delete u;
    }
    for (auto pc : privateChats) {
        delete pc.second;
    }
    for (auto cr : chatRooms) {
        delete cr.second;
    }

    logger.log("Application exited");
    return 0;
}