#include "PrivateChat.h"
#include <algorithm>

// Constructor
PrivateChat::PrivateChat(User* u1, User* u2) : user1(u1), user2(u2) {
    std::string name1 = u1->getUsername();
    std::string name2 = u2->getUsername();
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
    notifications.push("New message from " + msg->getSender());
}

// View history
void PrivateChat::viewHistory() {
    for (auto msg : messages) {
        msg->display();
        msg->setIsRead(true);
    }
}

// Search messages
std::vector<Message*> PrivateChat::searchMessages(std::string keyword) {
    std::vector<Message*> results;
    for (auto msg : messages) {
        if (msg->getContent().find(keyword) != std::string::npos) {
            results.push_back(msg);
        }
    }
    return results;
}

// Mark as read
void PrivateChat::markAsRead() {
    while (!notifications.empty()) {
        notifications.pop();
    }
}

// Get unread count
int PrivateChat::getUnreadCount() {
    return notifications.size();
}