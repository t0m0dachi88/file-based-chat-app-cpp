#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "User.h"
#include "PrivateChat.h"
#include "EncryptionManager.h"
#include <vector>
#include <string>
#include <fstream>

class FileManager {
private:
    std::string usersFile = "data/users.txt";
    std::string privateChatsDir = "data/private_chats/";

public:
    // Constructor
    FileManager();

    // Destructor
    ~FileManager();

    // Methods
    void saveUsers(const std::vector<User*>& users);
    std::vector<User*> loadUsers();

    void savePrivateChat(PrivateChat* chat);
    PrivateChat* loadPrivateChat(std::string id); // FIX 3: No dummy users created
    bool privateChatExists(std::string id);
    void deletePrivateChatFile(std::string id);

    // Helper
    std::string getUserType(User* u);
};

#endif