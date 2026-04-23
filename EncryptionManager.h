#ifndef ENCRYPTIONMANAGER_H
#define ENCRYPTIONMANAGER_H

#include <string>

class EncryptionManager {
private:
    int defaultShift = 3;

public:
    // Constructor
    EncryptionManager();

    // Destructor
    ~EncryptionManager();

    // Methods
    std::string encrypt(std::string text, int shift = 3);
    std::string decrypt(std::string text, int shift = 3);
};

#endif