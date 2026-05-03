#include "Admin.h"
#include <iostream>

// --- Constructor ---
Admin::Admin(const std::string& username, const std::string& password) 
    : User(username, password) {}

// --- Destructor ---
Admin::~Admin() = default;

// --- Override Methods ---

void Admin::displayProfile() const {
    std::cout << "[Admin Profile] Username: " << getUsername() << std::endl;
}

bool Admin::canModerate() const {
    return true;
}

// --- Admin Specific Methods ---

void Admin::removeUserFromRoom(const std::string& targetUsername) const {
    std::cout << "[Admin Action] " << getUsername() 
              << " removed user '" << targetUsername << "' from the room." << std::endl;
}

void Admin::muteUser(const std::string& targetUsername) const {
    std::cout << "[Admin Action] " << getUsername() 
              << " muted user '" << targetUsername << "'." << std::endl;
}