#include "FileManager.h"
#include "Admin.h"
#include "Member.h"
#include "TextMessage.h"
#include "EncryptedMessage.h"
#include "EncryptionManager.h"
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// --- Constructor ---
FileManager::FileManager() : usersFile_("data/users.txt"), privateChatsDir_("data/private_chats/") {
    // Ensure directories exist using modern C++ filesystem
    try {
        fs::create_directories("data");
        fs::create_directories(privateChatsDir_);
        fs::create_directories("data/logs");
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem Error: " << e.what() << std::endl;
    }
}

// --- Helper ---
std::string FileManager::getUserType(const User* u) const {
    if (dynamic_cast<const Admin*>(u)) return "Admin";
    if (dynamic_cast<const Member*>(u)) return "Member";
    return "Unknown";
}

// --- Save Users ---
void FileManager::saveUsers(const std::vector<std::unique_ptr<User>>& users) const {
    try {
        std::ofstream file(usersFile_);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open users file for writing.");
        }
        
        EncryptionManager em;
        for (const auto& u : users) {
            std::string encryptedPassword = em.encrypt(u->getPassword());
            std::string encryptedAnswer = em.encrypt(u->getSecurityAnswer());
            
            file << getUserType(u.get()) << "," 
                 << u->getUsername() << "," 
                 << encryptedPassword << "," 
                 << u->getSecurityQuestion() << "," 
                 << encryptedAnswer << "\n";
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "File Error saving users: " << e.what() << std::endl;
    }
}

// --- Load Users ---
std::vector<std::unique_ptr<User>> FileManager::loadUsers() const {
    std::vector<std::unique_ptr<User>> users;
    try {
        std::ifstream file(usersFile_);
        if (!file.is_open()) {
            // First run: file might not exist yet, which is fine
            return users;
        }

        std::string line;
        EncryptionManager em;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::stringstream ss(line);
            std::string type, username, password, question, answer;
            
            std::getline(ss, type, ',');
            std::getline(ss, username, ',');
            std::getline(ss, password, ',');
            std::getline(ss, question, ',');
            std::getline(ss, answer, ',');
            
            std::string decryptedPassword = em.decrypt(password);
            std::string decryptedAnswer = answer.empty() ? "" : em.decrypt(answer);
            
            std::unique_ptr<User> u;
            if (type == "Admin") {
                u = std::make_unique<Admin>(username, decryptedPassword);
            } else if (type == "Member") {
                u = std::make_unique<Member>(username, decryptedPassword);
            }
            
            if (u) {
                u->setSecurityQuestion(question);
                u->setSecurityAnswer(decryptedAnswer);
                users.push_back(std::move(u));
            }
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "File Error loading users: " << e.what() << std::endl;
    }
    return users;
}

// --- Save Private Chat ---
void FileManager::savePrivateChat(const PrivateChat* chat) const {
    if (!chat) return;
    
    try {
        std::string filename = privateChatsDir_ + chat->getId() + ".txt";
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open private chat file for writing.");
        }
        
        file << chat->getUser1() << "," << chat->getUser2() << "\n";
        
        EncryptionManager em;
        for (const auto& msg : chat->getMessages()) {
            // Determine content to save
            std::string contentToSave = msg->getContent();
            if (msg->getType() == "Encrypted") {
                // Ensure it's encrypted before writing to disk
                contentToSave = em.encrypt(contentToSave);
            }
            
            file << msg->getType() << "," 
                 << msg->getSender() << "," 
                 << contentToSave << "," 
                 << msg->getTimestamp() << "," 
                 << (msg->getIsRead() ? "1" : "0") << "\n";
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "File Error saving chat: " << e.what() << std::endl;
    }
}

// --- Load Private Chat ---
std::unique_ptr<PrivateChat> FileManager::loadPrivateChat(const std::string& id) const {
    try {
        std::string filename = privateChatsDir_ + id + ".txt";
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
        
        auto chat = std::make_unique<PrivateChat>(u1_str, u2_str);
        
        // Load messages
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::stringstream ss2(line);
            std::string type, sender, content, timestamp, isReadStr;
            
            std::getline(ss2, type, ',');
            std::getline(ss2, sender, ',');
            std::getline(ss2, content, ',');
            std::getline(ss2, timestamp, ',');
            std::getline(ss2, isReadStr, ',');
            
            std::unique_ptr<Message> msg;
            if (type == "Text") {
                msg = std::make_unique<TextMessage>(sender, content);
            } else if (type == "Encrypted") {
                EncryptionManager em;
                std::string plaintext = em.decrypt(content); // Decrypt so constructor can encrypt properly
                msg = std::make_unique<EncryptedMessage>(sender, plaintext);
            }
            
            if (msg) {
                msg->setIsRead(isReadStr == "1");
                msg->setTimestamp(timestamp);
                chat->addMessage(std::move(msg));
            }
        }
        file.close();
        return chat;
    } catch (const std::exception& e) {
        std::cerr << "File Error loading chat: " << e.what() << std::endl;
        return nullptr;
    }
}

// --- Check Exists ---
bool FileManager::privateChatExists(const std::string& id) const {
    std::string filename = privateChatsDir_ + id + ".txt";
    return fs::exists(filename);
}

// --- Delete File ---
void FileManager::deletePrivateChatFile(const std::string& id) const {
    try {
        std::string filename = privateChatsDir_ + id + ".txt";
        if (fs::exists(filename)) {
            fs::remove(filename);
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem Error deleting chat: " << e.what() << std::endl;
    }
}

// --- Get All Chat IDs ---
std::vector<std::string> FileManager::getAllChatIdsForUser(const std::string& username) const {
    std::vector<std::string> ids;
    try {
        if (!fs::exists(privateChatsDir_)) return ids;
        
        for (const auto& entry : fs::directory_iterator(privateChatsDir_)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                std::string filename = entry.path().stem().string(); // Get filename without extension
                
                std::string search1 = username + "_";
                std::string search2 = "_" + username;
                
                // Check if id starts with search1 or ends with search2
                if (filename.find(search1) == 0 || 
                   (filename.length() >= search2.length() && 
                    filename.compare(filename.length() - search2.length(), search2.length(), search2) == 0)) {
                    ids.push_back(filename);
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem Error listing chats: " << e.what() << std::endl;
    }
    return ids;
}