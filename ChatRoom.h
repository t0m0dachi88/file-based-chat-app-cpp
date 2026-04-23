#ifndef CHATROOM_H
#define CHATROOM_H

#include "User.h"
#include "Message.h"
#include "Admin.h"
#include <vector>
#include <set>
#include <string>

class ChatRoom {
private:
    std::string name;
    Admin* admin;
    std::vector<User*> members; // STL vector
    std::set<std::string> mutedUsers; // STL set
    std::vector<Message*> messages; // STL vector

public:
    // Constructor
    ChatRoom(std::string n, Admin* a);

    // Destructor
    ~ChatRoom();

    // Methods
    void addMember(User* u);
    void removeMember(std::string username);
    void sendMessage(Message* msg);
    void viewHistory();
    void muteUser(std::string username);
    void unmuteUser(std::string username);
    bool isMuted(std::string username);

    // Getters
    std::string getName() const { return name; }
    Admin* getAdmin() const { return admin; }
    std::vector<Message*> getMessages() const { return messages; }
};

#endif