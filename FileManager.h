#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "User.h"
#include "PrivateChat.h"
#include "ChatRoom.h"
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
    std::string roomChatsDir = "data/room_chats/";

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

    void saveChatRoom(ChatRoom* room);
    ChatRoom* loadChatRoom(std::string name);

    // Helper
    std::string getUserType(User* u);
};

#endif