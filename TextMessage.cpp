#include "TextMessage.h"

// --- Constructor ---
TextMessage::TextMessage(const std::string& sender, const std::string& content) 
    : Message(sender, content) {}

// --- Destructor ---
TextMessage::~TextMessage() = default;

// --- Override Methods ---

void TextMessage::display() const {
    std::cout << *this << std::endl;
}

std::string TextMessage::getType() const {
    return "Text";
}