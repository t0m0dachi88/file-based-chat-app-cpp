#ifndef ENCRYPTEDMESSAGE_H
#define ENCRYPTEDMESSAGE_H

#include "Message.h"
#include "EncryptionManager.h"

/// @brief Represents a message that is stored in an encrypted format.
/// Demonstrates composition (using EncryptionManager) to avoid code duplication.
class EncryptedMessage : public Message {
private:
    int shift_;
    EncryptionManager encryptionManager_;

public:
    // Constructor
    EncryptedMessage(const std::string& sender, const std::string& content, int shift = 3);

    // Destructor
    ~EncryptedMessage() override;

    // Override virtual methods
    void display() const override;
    std::string getType() const override;
    std::string getContent() const override;
};

#endif // ENCRYPTEDMESSAGE_H