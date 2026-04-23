#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"

class Member : public User {
public:
    // Constructor
    Member(std::string u, std::string p);

    // Destructor
    ~Member();

    // Override virtual methods
    void displayProfile() override;
    bool canModerate() override;

    // Member specific methods
    void changePassword(std::string newPass);
};

#endif