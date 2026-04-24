#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include "Message.h"
#include <vector>
#include <string>

class PrivateChat {
private:
    std::string id;
    std::string user1; // FIX 2: Dangling pointer fix, use string
    std::string user2;
    std::vector<Message*> messages; // STL vector

public:
    // Constructor
    PrivateChat(std::string u1, std::string u2);

    // Destructor
    ~PrivateChat();

    // Methods
    void sendMessage(Message* msg);
    void viewHistory();
    void markAsRead();
    int getUnreadCount() const;

    // Getters
    std::string getId() const { return id; }
    std::string getUser1() const { return user1; }
    std::string getUser2() const { return user2; }
    const std::vector<Message*>& getMessages() const { return messages; } // Const reference
};

#endif