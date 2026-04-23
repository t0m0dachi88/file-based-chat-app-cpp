#include "ChatRoom.h"
#include <algorithm>

// Constructor
ChatRoom::ChatRoom(std::string n, Admin* a) : name(n), admin(a) {
    members.push_back(a); // admin is a member
}

// Destructor
ChatRoom::~ChatRoom() {
    for (auto msg : messages) {
        delete msg;
    }
}

// Add member
void ChatRoom::addMember(User* u) {
    members.push_back(u);
}

// Remove member (admin only)
void ChatRoom::removeMember(std::string username) {
    if (admin->getUsername() == username) return; // can't remove admin
    auto it = std::find_if(members.begin(), members.end(), [&](User* u){ return u->getUsername() == username; });
    if (it != members.end()) {
        members.erase(it);
    }
}

// Send message
void ChatRoom::sendMessage(Message* msg) {
    if (isMuted(msg->getSender())) {
        std::cout << msg->getSender() << " is muted and cannot send messages." << std::endl;
        return;
    }
    messages.push_back(msg);
}

// View history
void ChatRoom::viewHistory() {
    for (auto msg : messages) {
        msg->display();
    }
}

// Mute user
void ChatRoom::muteUser(std::string username) {
    mutedUsers.insert(username);
}

// Unmute user
void ChatRoom::unmuteUser(std::string username) {
    mutedUsers.erase(username);
}

// Check if muted
bool ChatRoom::isMuted(std::string username) {
    return mutedUsers.find(username) != mutedUsers.end();
}