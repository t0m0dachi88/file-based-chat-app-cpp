#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <ctime>

// Abstract base class for User
class User {
protected:
    std::string username;
    std::string password;
    bool isOnline;
    std::set<std::string> blockedUsers; // STL set for blocked users
    int loginAttempts;
    static const int MAX_LOGIN_ATTEMPTS = 3;

public:
    // Constructor
    User(std::string u, std::string p);

    // Pure virtual destructor for polymorphism
    virtual ~User() = 0;

    // Pure virtual methods
    virtual void displayProfile() = 0;
    virtual bool canModerate() = 0;

    // Getters and setters
    std::string getUsername() const { return username; }
    bool getIsOnline() const { return isOnline; }
    std::string getPassword() const { return password; }

    void setPassword(std::string p) { password = p; }

    // Methods
    bool login(std::string p);
    void logout();
    void blockUser(std::string u);
    void unblockUser(std::string u);
    bool isBlocked(std::string u) const;

    // Type conversion operator (FIX 5)
    operator std::string() const { return username; }

    // Operator overloading for output
    friend std::ostream& operator<<(std::ostream& os, const User& u);
};

#endif