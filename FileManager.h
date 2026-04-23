#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "User.h"
#include "PrivateChat.h"
#include "EncryptionManager.h"
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

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
    void saveUsers(std::vector<User*> users);
    std::vector<User*> loadUsers();

    void savePrivateChat(PrivateChat* chat);
    PrivateChat* loadPrivateChat(std::string id, std::vector<User*>& users);
    bool privateChatExists(std::string id);

    // Helper
    std::string getUserType(User* u);
};

#endif