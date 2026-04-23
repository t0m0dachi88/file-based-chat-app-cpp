#include "Message.h"

// Constructor
Message::Message(std::string s, std::string c) : sender(s), content(c), isRead(false) {
    // Get current timestamp
    std::time_t now = std::time(nullptr);
    timestamp = std::ctime(&now);
    timestamp.erase(timestamp.find_last_not_of(" \n\r\t") + 1); // trim
}

// Pure virtual destructor
Message::~Message() {}

// Operator overloading
std::ostream& operator<<(std::ostream& os, const Message& m) {
    os << "[" << m.timestamp << "] " << m.sender << ": " << m.content;
    return os;
}