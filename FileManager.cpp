#include "FileManager.h"
#include "Admin.h"
#include "Member.h"
#include "TextMessage.h"
#include "EncryptedMessage.h"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdio>

// Constructor
FileManager::FileManager() {}

// Destructor
FileManager::~FileManager() {}

// Save users
void FileManager::saveUsers(const std::vector<User*>& users) {
    try {
        std::ofstream file(usersFile);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open users file for writing.");
        }
        for (auto u : users) {
            file << getUserType(u) << "," << u->getUsername() << "," << u->getPassword() << std::endl;
        }
        file.close();
    } catch (const std::exception& e) { // FIX 7: Exception handling
        std::cerr << "File Error: " << e.what() << std::endl;
    }
}

// Load users
std::vector<User*> FileManager::loadUsers() {
    std::vector<User*> users;
    try {
        std::ifstream file(usersFile);
        if (!file.is_open()) {
            // It's okay if file doesn't exist on first run
            return users;
        }
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string type, username, password;
            std::getline(ss, type, ',');
            std::getline(ss, username, ',');
            std::getline(ss, password, ',');
            if (type == "Admin") {
                users.push_back(new Admin(username, password));
            } else if (type == "Member") {
                users.push_back(new Member(username, password));
            }
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "File Error: " << e.what() << std::endl;
    }
    return users;
}

// Save private chat
void FileManager::savePrivateChat(PrivateChat* chat) {
    try {
        std::string filename = privateChatsDir + chat->getId() + ".txt";
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open private chat file for writing.");
        }
        file << chat->getUser1() << "," << chat->getUser2() << std::endl;
        EncryptionManager em;
        for (auto msg : chat->getMessages()) {
            std::string contentToSave = msg->getContent();
            if (msg->getType() == "Encrypted") {
                contentToSave = em.decrypt(contentToSave, 3);
            }
            file << msg->getType() << "," << msg->getSender() << "," << contentToSave << "," << msg->getTimestamp() << "," << (msg->getIsRead() ? "1" : "0") << std::endl;
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "File Error: " << e.what() << std::endl;
    }
}

// Load private chat
PrivateChat* FileManager::loadPrivateChat(std::string id) {
    try {
        std::string filename = privateChatsDir + id + ".txt";
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open private chat file for reading.");
        }
        std::string line;
        if (!std::getline(file, line)) {
             throw std::runtime_error("Private chat file is empty.");
        }
        std::stringstream ss(line);
        std::string u1_str, u2_str;
        std::getline(ss, u1_str, ',');
        std::getline(ss, u2_str, ',');
        
        PrivateChat* chat = new PrivateChat(u1_str, u2_str);
        
        // Load messages
        while (std::getline(file, line)) {
            std::stringstream ss2(line);
            std::string type, sender, content, timestamp, isReadStr;
            std::getline(ss2, type, ',');
            std::getline(ss2, sender, ',');
            std::getline(ss2, content, ',');
            std::getline(ss2, timestamp, ',');
            std::getline(ss2, isReadStr, ',');
            Message* msg = nullptr;
            if (type == "Text") {
                msg = new TextMessage(sender, content);
            } else if (type == "Encrypted") {
                msg = new EncryptedMessage(sender, content, 3);
            }
            if (msg) {
                msg->setIsRead(isReadStr == "1");
                msg->setTimestamp(timestamp); // FIX 1: Set the proper timestamp loaded from file
                chat->sendMessage(msg); // add to messages
            }
        }
        file.close();
        return chat;
    } catch (const std::exception& e) {
        std::cerr << "File Error: " << e.what() << std::endl;
        return nullptr;
    }
}

// Check if private chat exists
bool FileManager::privateChatExists(std::string id) {
    std::string filename = privateChatsDir + id + ".txt";
    std::ifstream file(filename);
    return file.good();
}

// Delete private chat file
void FileManager::deletePrivateChatFile(std::string id) {
    std::string filename = privateChatsDir + id + ".txt";
    std::remove(filename.c_str());
}

// Get user type
std::string FileManager::getUserType(User* u) {
    if (dynamic_cast<Admin*>(u)) return "Admin";
    if (dynamic_cast<Member*>(u)) return "Member";
    return "Unknown";
}