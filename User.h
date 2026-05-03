#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <iostream>
#include <stdexcept>

/// @brief Abstract base class representing a user in the chat system.
/// Demonstrates: abstract class, pure virtual functions, operator overloading,
/// type conversion operator, encapsulation, and STL set usage.
class User {
private:
    std::string username_;
    std::string password_;
    std::string securityQuestion_;
    std::string securityAnswer_;
    bool isOnline_;
    std::set<std::string> blockedUsers_;  // STL set for O(log n) lookup
    int loginAttempts_;
    static const int kMaxLoginAttempts = 3;

public:
    // Constructor
    explicit User(const std::string& username, const std::string& password);

    // Pure virtual destructor for polymorphism
    virtual ~User() = 0;

    // Pure virtual methods (runtime polymorphism)
    virtual void displayProfile() const = 0;
    virtual bool canModerate() const = 0;

    // --- Getters (const-correct) ---
    const std::string& getUsername() const { return username_; }
    const std::string& getPassword() const { return password_; }
    bool getIsOnline() const { return isOnline_; }
    const std::string& getSecurityQuestion() const { return securityQuestion_; }
    const std::string& getSecurityAnswer() const { return securityAnswer_; }
    const std::set<std::string>& getBlockedUsers() const { return blockedUsers_; }

    // --- Setters (validated) ---
    void setPassword(const std::string& password);
    void setSecurityQuestion(const std::string& question);
    void setSecurityAnswer(const std::string& answer);

    // Security verification
    bool checkSecurityAnswer(const std::string& answer) const;

    // Authentication
    bool login(const std::string& password);
    void logout();

    // Block management
    void blockUser(const std::string& username);
    void unblockUser(const std::string& username);
    bool isBlocked(const std::string& username) const;

    // Type conversion operator (compile-time polymorphism demonstration)
    explicit operator std::string() const { return username_; }

    // Operator overloading for output
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};

#endif // USER_H