#include "User.h"
#include <algorithm>

// Constructor
User::User(std::string u, std::string p, std::string e)
    : username(u), password(p), email(e), isOnline(false), loginAttempts(0) {}

// Pure virtual destructor
User::~User() {}

// Login with attempt limit
bool User::login(std::string p) {
    if (loginAttempts >= MAX_LOGIN_ATTEMPTS) {
        std::cout << "Too many failed attempts. Account locked." << std::endl;
        return false;
    }
    if (password == p) {
        isOnline = true;
        loginAttempts = 0;
        return true;
    } else {
        loginAttempts++;
        return false;
    }
}

void User::logout() {
    isOnline = false;
}

void User::blockUser(std::string u) {
    blockedUsers.insert(u);
}

void User::unblockUser(std::string u) {
    blockedUsers.erase(u);
}

bool User::isBlocked(std::string u) const {
    return blockedUsers.find(u) != blockedUsers.end();
}

// Operator overloading
std::ostream& operator<<(std::ostream& os, const User& u) {
    os << "Username: " << u.username << ", Email: " << u.email << ", Online: " << (u.isOnline ? "Yes" : "No");
    return os;
}