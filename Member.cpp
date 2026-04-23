#include "Member.h"

// Constructor
Member::Member(std::string u, std::string p) : User(u, p) {}

// Destructor
Member::~Member() {}

// Override displayProfile
void Member::displayProfile() {
    std::cout << "Member Profile: " << username << std::endl;
}

// Override canModerate
bool Member::canModerate() {
    return false;
}

// Member method
void Member::changePassword(std::string newPass) {
    password = newPass;
    std::cout << "Password changed for " << username << std::endl;
}