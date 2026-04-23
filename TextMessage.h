#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "Message.h"

class TextMessage : public Message {
public:
    // Constructor
    TextMessage(std::string s, std::string c);

    // Destructor
    ~TextMessage();

    // Override virtual methods
    void display() override;
    std::string getType() override;
};

#endif