#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "Message.h"

/// @brief Represents a standard, unencrypted text message.
class TextMessage : public Message {
public:
    // Constructor
    TextMessage(const std::string& sender, const std::string& content);

    // Destructor
    ~TextMessage() override;

    // Override virtual methods
    void display() const override;
    std::string getType() const override;
};

#endif // TEXTMESSAGE_H