#ifndef ENCRYPTEDMESSAGE_H
#define ENCRYPTEDMESSAGE_H

#include "Message.h"

class EncryptedMessage : public Message {
private:
    int shift; // for Caesar cipher

public:
    // Constructor
    EncryptedMessage(std::string s, std::string c, int sh = 3);

    // Destructor
    ~EncryptedMessage();

    // Override virtual methods
    void display() override;
    std::string getType() override;

    // Encryption methods
    std::string encrypt(std::string text);
    std::string decrypt(std::string text);
};

#endif