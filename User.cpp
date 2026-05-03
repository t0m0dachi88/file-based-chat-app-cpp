#include "User.h"

// --- Constructor ---
User::User(const std::string& username, const std::string& password)
    : username_(username), password_(password), isOnline_(false), loginAttempts_(0) {
    if (username.empty()) {
        throw std::invalid_argument("Username cannot be empty.");
    }
    if (password.empty()) {
        throw std::invalid_argument("Password cannot be empty.");
    }
}

// Pure virtual destructor definition (required for linkage)
User::~User() {}

// --- Setters with validation ---

void User::setPassword(const std::string& password) {
    if (password.empty()) {
        throw std::invalid_argument("Password cannot be empty.");
    }
    password_ = password;
}

void User::setSecurityQuestion(const std::string& question) {
    securityQuestion_ = question;
}

void User::setSecurityAnswer(const std::string& answer) {
    securityAnswer_ = answer;
}

// --- Security verification ---

bool User::checkSecurityAnswer(const std::string& answer) const {
    return securityAnswer_ == answer;
}

// --- Authentication ---

bool User::login(const std::string& password) {
    if (loginAttempts_ >= kMaxLoginAttempts) {
        std::cout << "Too many failed attempts. Account locked." << std::endl;
        return false;
    }
    if (password_ == password) {
        isOnline_ = true;
        loginAttempts_ = 0;
        return true;
    }
    ++loginAttempts_;
    return false;
}

void User::logout() {
    isOnline_ = false;
}

// --- Block management ---

void User::blockUser(const std::string& username) {
    if (username.empty()) {
        throw std::invalid_argument("Cannot block an empty username.");
    }
    blockedUsers_.insert(username);
}

void User::unblockUser(const std::string& username) {
    blockedUsers_.erase(username);
}

bool User::isBlocked(const std::string& username) const {
    return blockedUsers_.count(username) > 0;
}

// --- Operator overloading ---

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "Username: " << user.username_
       << " | Status: " << (user.isOnline_ ? "Online" : "Offline");
    return os;
}