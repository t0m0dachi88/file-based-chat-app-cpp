#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include "User.h"
#include "Message.h"
#include <vector>
#include <queue>
#include <string>

class PrivateChat {
private:
    std::string id;
    User* user1;
    User* user2;
    std::vector<Message*> messages; // STL vector
    std::queue<std::string> notifications; // STL queue for unread notifications

public:
    // Constructor
    PrivateChat(User* u1, User* u2);

    // Destructor
    ~PrivateChat();

    // Methods
    void sendMessage(Message* msg);
    void viewHistory();
    std::vector<Message*> searchMessages(std::string keyword);
    void markAsRead();
    int getUnreadCount();

    // Getters
    std::string getId() const { return id; }
    User* getUser1() const { return user1; }
    User* getUser2() const { return user2; }
    std::vector<Message*> getMessages() const { return messages; }
};

#endif