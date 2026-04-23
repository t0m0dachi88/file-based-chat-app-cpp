#include "Admin.h"

// Constructor
Admin::Admin(std::string u, std::string p, std::string e) : User(u, p, e) {}

// Destructor
Admin::~Admin() {}

// Override displayProfile
void Admin::displayProfile() {
    std::cout << "Admin Profile: " << username << " (" << email << ")" << std::endl;
}

// Override canModerate
bool Admin::canModerate() {
    return true;
}

// Admin methods
void Admin::removeUserFromRoom(std::string username) {
    std::cout << "Admin " << this->username << " removed user " << username << " from room." << std::endl;
}

void Admin::muteUser(std::string username) {
    std::cout << "Admin " << this->username << " muted user " << username << "." << std::endl;
}