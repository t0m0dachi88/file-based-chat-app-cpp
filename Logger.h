#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

// Template class for logging
template <typename T>
class Logger {
private:
    std::string logFile;

public:
    // Constructor
    Logger(std::string file) : logFile("data/logs/" + file + ".log") {}

    // Destructor
    ~Logger() {}

    // Log method
    void log(T message) {
        std::ofstream file(logFile, std::ios::app);
        std::time_t now = std::time(nullptr);
        std::string timestamp = std::ctime(&now);
        timestamp.erase(timestamp.find_last_not_of(" \n\r\t") + 1);
        file << "[" << timestamp << "] " << message << std::endl;
        file.close();
        std::cout << "Logged: " << message << std::endl;
    }
};

#endif