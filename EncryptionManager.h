#ifndef ENCRYPTIONMANAGER_H
#define ENCRYPTIONMANAGER_H

#include <string>

/// @brief Utility class for handling string encryption and decryption.
/// Uses a basic Caesar cipher for demonstration purposes.
class EncryptionManager {
private:
    static const int kDefaultShift = 3;

public:
    // Constructor
    EncryptionManager() = default;

    // Destructor
    ~EncryptionManager() = default;

    // --- Core Operations ---
    
    /// @brief Encrypts a string using Caesar cipher.
    std::string encrypt(const std::string& text, int shift = kDefaultShift) const;

    /// @brief Decrypts a string using Caesar cipher.
    std::string decrypt(const std::string& text, int shift = kDefaultShift) const;
};

#endif // ENCRYPTIONMANAGER_H