#include "PrivateChat.h"
#include <algorithm>
#include <iostream>

// Constructor
PrivateChat::PrivateChat(std::string u1, std::string u2) : user1(u1), user2(u2) {
    std::string name1 = u1;
    std::string name2 = u2;
    if (name1 > name2) std::swap(name1, name2);
    id = name1 + "_" + name2;
}

// Destructor
PrivateChat::~PrivateChat() {
    for (auto msg : messages) {
        delete msg;
    }
}

// Send message
void PrivateChat::sendMessage(Message* msg) {
    messages.push_back(msg);
}

// View history
void PrivateChat::viewHistory() {
    for (auto msg : messages) {
        msg->display();
        msg->setIsRead(true);
    }
}

// Mark as read
void PrivateChat::markAsRead() {
    for (auto msg : messages) {
        msg->setIsRead(true);
    }
}

// Get unread count
int PrivateChat::getUnreadCount() const {
    int count = 0;
    for (auto msg : messages) {
        if (!msg->getIsRead()) {
            count++;
        }
    }
    return count;
}