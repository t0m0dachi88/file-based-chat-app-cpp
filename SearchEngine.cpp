#include "SearchEngine.h"

// Constructor
SearchEngine::SearchEngine() {}

// Destructor
SearchEngine::~SearchEngine() {}

// Search by keyword
std::vector<Message*> SearchEngine::searchByKeyword(std::vector<Message*> messages, std::string keyword) {
    std::vector<Message*> results;
    for (auto msg : messages) {
        if (msg->getContent().find(keyword) != std::string::npos) {
            results.push_back(msg);
        }
    }
    return results;
}

// Search by sender
std::vector<Message*> SearchEngine::searchBySender(std::vector<Message*> messages, std::string sender) {
    std::vector<Message*> results;
    for (auto msg : messages) {
        if (msg->getSender() == sender) {
            results.push_back(msg);
        }
    }
    return results;
}

// Search by date (simplified, check if timestamp contains date)
std::vector<Message*> SearchEngine::searchByDate(std::vector<Message*> messages, std::string date) {
    std::vector<Message*> results;
    for (auto msg : messages) {
        if (msg->getTimestamp().find(date) != std::string::npos) {
            results.push_back(msg);
        }
    }
    return results;
}