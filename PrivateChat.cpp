#include "PrivateChat.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

// --- Constructor ---
PrivateChat::PrivateChat(const std::string& user1, const std::string& user2) 
    : user1_(user1), user2_(user2) {
    
    if (user1.empty() || user2.empty()) {
        throw std::invalid_argument("Users cannot be empty for PrivateChat.");
    }

    std::string name1 = user1;
    std::string name2 = user2;
    // Ensure consistent ID generation regardless of parameter order
    if (name1 > name2) {
        std::swap(name1, name2);
    }
    id_ = name1 + "_" + name2;
}

// --- Methods ---

void PrivateChat::addMessage(std::unique_ptr<Message> msg) {
    if (!msg) {
        throw std::invalid_argument("Cannot add a null message.");
    }
    messages_.push_back(std::move(msg));
}

void PrivateChat::viewHistory() const {
    if (messages_.empty()) {
        std::cout << "No messages in this chat yet." << std::endl;
        return;
    }
    
    for (const auto& msg : messages_) {
        msg->display();
        // Since viewHistory is const, we shouldn't modify the messages.
        // We'll leave the markAsRead to be called explicitly by the UI.
    }
}

void PrivateChat::markAsRead() {
    for (auto& msg : messages_) {
        msg->setIsRead(true);
    }
}

int PrivateChat::getUnreadCount() const {
    int count = 0;
    for (const auto& msg : messages_) {
        if (!msg->getIsRead()) {
            count++;
        }
    }
    return count;
}