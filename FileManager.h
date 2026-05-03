#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "User.h"
#include "PrivateChat.h"
#include <vector>
#include <string>
#include <memory>

/// @brief Handles persistent storage of users and chats.
/// Refactored to use std::unique_ptr for memory safety and std::filesystem internally.
class FileManager {
private:
    std::string usersFile_;
    std::string privateChatsDir_;

    // Helper to determine the concrete type of a polymorphic User object
    std::string getUserType(const User* u) const;

public:
    // Constructor
    FileManager();

    // Destructor
    ~FileManager() = default;

    // --- User Data ---
    void saveUsers(const std::vector<std::unique_ptr<User>>& users) const;
    std::vector<std::unique_ptr<User>> loadUsers() const;

    // --- Chat Data ---
    void savePrivateChat(const PrivateChat* chat) const;
    std::unique_ptr<PrivateChat> loadPrivateChat(const std::string& id) const;
    bool privateChatExists(const std::string& id) const;
    void deletePrivateChatFile(const std::string& id) const;
    std::vector<std::string> getAllChatIdsForUser(const std::string& username) const;
};

#endif // FILEMANAGER_H