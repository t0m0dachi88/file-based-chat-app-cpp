#include "EncryptedMessage.h"

// Constructor
EncryptedMessage::EncryptedMessage(std::string s, std::string c, int sh) : Message(s, c), shift(sh) {
    content = encrypt(c); // encrypt on creation
}

// Destructor
EncryptedMessage::~EncryptedMessage() {}

// Override display - decrypt for display
void EncryptedMessage::display() {
    std::string decrypted = decrypt(content);
    std::cout << "[" << timestamp << "] " << sender << ": " << decrypted << " (Encrypted)" << std::endl;
}

// Override getType
std::string EncryptedMessage::getType() {
    return "Encrypted";
}

// Override getContent
std::string EncryptedMessage::getContent() const {
    return decrypt(content);
}

// Simple Caesar cipher encrypt
std::string EncryptedMessage::encrypt(std::string text) const {
    std::string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base + shift) % 26 + base;
        }
    }
    return result;
}

// Decrypt
std::string EncryptedMessage::decrypt(std::string text) const {
    std::string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base - shift + 26) % 26 + base;
        }
    }
    return result;
}