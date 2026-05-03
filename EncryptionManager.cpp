#include "EncryptionManager.h"
#include <cctype>

std::string EncryptionManager::encrypt(const std::string& text, int shift) const {
    std::string result = text;
    for (char& c : result) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            // Safe modulo arithmetic for Caesar cipher
            c = static_cast<char>((c - base + shift) % 26 + base);
        } else if (std::isdigit(c)) {
            c = static_cast<char>((c - '0' + shift) % 10 + '0');
        }
    }
    return result;
}

std::string EncryptionManager::decrypt(const std::string& text, int shift) const {
    std::string result = text;
    for (char& c : result) {
        if (std::isalpha(c)) {
            char base = std::isupper(c) ? 'A' : 'a';
            // Added 26 to avoid negative modulo results
            c = static_cast<char>((c - base - shift % 26 + 26) % 26 + base);
        } else if (std::isdigit(c)) {
            // Added 10 to avoid negative modulo results
            c = static_cast<char>((c - '0' - shift % 10 + 10) % 10 + '0');
        }
    }
    return result;
}