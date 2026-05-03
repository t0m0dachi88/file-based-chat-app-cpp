#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdexcept>

/// @brief Template class for generic logging to a file.
template <typename T>
class Logger {
private:
    std::string logFile_;

public:
    // Constructor
    explicit Logger(const std::string& fileName) : logFile_("data/logs/" + fileName + ".log") {}

    // Destructor
    ~Logger() = default;

    // Log method
    void log(const T& message) const {
        std::ofstream file(logFile_, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Warning: Could not open log file: " << logFile_ << std::endl;
            return;
        }

        std::time_t now = std::time(nullptr);
        std::string timestamp = std::ctime(&now);
        
        // Safe trim of newline
        size_t endpos = timestamp.find_last_not_of(" \n\r\t");
        if (std::string::npos != endpos) {
            timestamp = timestamp.substr(0, endpos + 1);
        }

        file << "[" << timestamp << "] " << message << std::endl;
        file.close();
        
        // Optional: print to console
        // std::cout << "Logged: " << message << std::endl;
    }
};

#endif // LOGGER_H