#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"
#include <string>

/// @brief Member class inheriting from User. Represents a regular user.
class Member : public User {
public:
    // Constructor
    Member(const std::string& username, const std::string& password);

    // Destructor
    ~Member() override;

    // Override virtual methods
    void displayProfile() const override;
    bool canModerate() const override;

    // Member specific methods
    void changePassword(const std::string& newPassword);
};

#endif // MEMBER_H