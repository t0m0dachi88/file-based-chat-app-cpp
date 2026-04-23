#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    // Constructor
    Admin(std::string u, std::string p);

    // Destructor
    ~Admin();

    // Override virtual methods
    void displayProfile() override;
    bool canModerate() override;

    // Admin specific methods
    void removeUserFromRoom(std::string username);
    void muteUser(std::string username);
};

#endif