#include "FileManager.h"
#include "Admin.h"
#include "Member.h"
#include "TextMessage.h"
#include "EncryptedMessage.h"
#include <sstream>

// Constructor
FileManager::FileManager() {}

// Destructor
FileManager::~FileManager() {}

// Save users
void FileManager::saveUsers(std::vector<User*> users) {
    std::ofstream file(usersFile);
    for (auto u : users) {
        file << getUserType(u) << "," << u->getUsername() << "," << u->getPassword() << std::endl;
    }
    file.close();
}

// Load users
std::vector<User*> FileManager::loadUsers() {
    std::vector<User*> users;
    std::ifstream file(usersFile);
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
    return users;
}

// Save private chat
void FileManager::savePrivateChat(PrivateChat* chat) {
    std::string filename = privateChatsDir + chat->getId() + ".txt";
    std::ofstream file(filename);
    file << chat->getUser1()->getUsername() << "," << chat->getUser2()->getUsername() << std::endl;
    EncryptionManager em;
    for (auto msg : chat->getMessages()) {
        std::string contentToSave = msg->getContent();
        if (msg->getType() == "Encrypted") {
            contentToSave = em.decrypt(contentToSave, 3);
        }
        file << msg->getType() << "," << msg->getSender() << "," << contentToSave << "," << msg->getTimestamp() << "," << (msg->getIsRead() ? "1" : "0") << std::endl;
    }
    file.close();
}

// Load private chat
PrivateChat* FileManager::loadPrivateChat(std::string id, std::vector<User*>& users) {
    std::string filename = privateChatsDir + id + ".txt";
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::string u1_str, u2_str;
    std::getline(ss, u1_str, ',');
    std::getline(ss, u2_str, ',');
    User* user1 = nullptr;
    User* user2 = nullptr;
    for (auto u : users) {
        if (u->getUsername() == u1_str) user1 = u;
        if (u->getUsername() == u2_str) user2 = u;
    }
    if (!user1) user1 = new Member(u1_str, "pass");
    if (!user2) user2 = new Member(u2_str, "pass");
    PrivateChat* chat = new PrivateChat(user1, user2);
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
            chat->sendMessage(msg); // add to messages
        }
    }
    file.close();
    return chat;
}

// Check if private chat exists
bool FileManager::privateChatExists(std::string id) {
    std::string filename = privateChatsDir + id + ".txt";
    std::ifstream file(filename);
    return file.good();
}

// Get user type
std::string FileManager::getUserType(User* u) {
    if (dynamic_cast<Admin*>(u)) return "Admin";
    if (dynamic_cast<Member*>(u)) return "Member";
    return "Unknown";
}