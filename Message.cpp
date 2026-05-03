#include "Message.h"
#include <ctime>
#include <stdexcept>

// --- Constructor ---
Message::Message(const std::string& sender, const std::string& content) 
    : sender_(sender), content_(content), isRead_(false) {
    
    if (sender.empty()) {
        throw std::invalid_argument("Sender cannot be empty.");
    }
    if (content.empty()) {
        throw std::invalid_argument("Message content cannot be empty.");
    }

    // Generate current timestamp
    std::time_t now = std::time(nullptr);
    timestamp_ = std::ctime(&now);
    
    // Trim newline from ctime output
    size_t endpos = timestamp_.find_last_not_of(" \n\r\t");
    if (std::string::npos != endpos) {
        timestamp_ = timestamp_.substr(0, endpos + 1);
    }
}

// --- Destructor ---
Message::~Message() = default;

// --- Operator Overloading ---
std::ostream& operator<<(std::ostream& os, const Message& msg) {
    os << "[" << msg.timestamp_ << "] " << msg.sender_ << ": " << msg.content_;
    return os;
}