#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <string>

/// @brief Admin class inheriting from User. Demonstrates inheritance and polymorphism.
class Admin : public User {
public:
    // Constructor
    Admin(const std::string& username, const std::string& password);

    // Destructor
    ~Admin() override;

    // Override virtual methods
    void displayProfile() const override;
    bool canModerate() const override;

    // Admin specific methods
    void removeUserFromRoom(const std::string& username) const;
    void muteUser(const std::string& username) const;
};

#endif // ADMIN_H