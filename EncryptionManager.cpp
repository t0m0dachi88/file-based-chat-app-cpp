#include "EncryptionManager.h"

// Constructor
EncryptionManager::EncryptionManager() {}

// Destructor
EncryptionManager::~EncryptionManager() {}

// Encrypt
std::string EncryptionManager::encrypt(std::string text, int shift) {
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
std::string EncryptionManager::decrypt(std::string text, int shift) {
    std::string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = (c - base - shift + 26) % 26 + base;
        }
    }
    return result;
}