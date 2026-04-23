#include "TextMessage.h"

// Constructor
TextMessage::TextMessage(std::string s, std::string c) : Message(s, c) {}

// Destructor
TextMessage::~TextMessage() {}

// Override display
void TextMessage::display() {
    std::cout << *this << std::endl;
}

// Override getType
std::string TextMessage::getType() {
    return "Text";
}