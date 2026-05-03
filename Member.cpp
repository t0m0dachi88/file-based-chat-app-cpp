#include "Member.h"
#include <iostream>
#include <stdexcept>

// --- Constructor ---
Member::Member(const std::string& username, const std::string& password) 
    : User(username, password) {}

// --- Destructor ---
Member::~Member() = default;

// --- Override Methods ---

void Member::displayProfile() const {
    std::cout << "[Member Profile] Username: " << getUsername() << std::endl;
}

bool Member::canModerate() const {
    return false;
}

// --- Member Specific Methods ---

void Member::changePassword(const std::string& newPassword) {
    if (newPassword.empty()) {
        throw std::invalid_argument("New password cannot be empty.");
    }
    setPassword(newPassword);
    std::cout << "[Success] Password changed successfully for user: " << getUsername() << std::endl;
}