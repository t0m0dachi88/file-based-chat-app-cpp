#include "EncryptedMessage.h"
#include <iostream>

// --- Constructor ---
// Note: We immediately encrypt the content for secure storage in memory
EncryptedMessage::EncryptedMessage(const std::string& sender, const std::string& content, int shift) 
    : Message(sender, content), shift_(shift) { 
    
    // Encrypt the incoming plaintext content and store it in base class field
    content_ = encryptionManager_.encrypt(content, shift_);
}

// --- Destructor ---
EncryptedMessage::~EncryptedMessage() = default;

// --- Override Methods ---

void EncryptedMessage::display() const {
    // Decrypt on the fly for display
    std::string decrypted = encryptionManager_.decrypt(content_, shift_);
    std::cout << "[" << timestamp_ << "] " << sender_ << ": " << decrypted << " (Encrypted)" << std::endl;
}

std::string EncryptedMessage::getType() const {
    return "Encrypted";
}

std::string EncryptedMessage::getContent() const {
    // Return decrypted content when asked (e.g. for searching)
    return encryptionManager_.decrypt(content_, shift_);
}