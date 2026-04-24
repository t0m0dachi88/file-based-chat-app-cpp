#include "SearchEngine.h"

// Constructor
SearchEngine::SearchEngine() {}

// Destructor
SearchEngine::~SearchEngine() {}

// Search by keyword
std::vector<Message*> SearchEngine::search(const std::vector<Message*>& messages, std::string keyword) {
    std::vector<Message*> results;
    for (auto msg : messages) {
        if (msg->getContent().find(keyword) != std::string::npos) {
            results.push_back(msg);
        }
    }
    return results;
}

// Search by keyword and sender
std::vector<Message*> SearchEngine::search(const std::vector<Message*>& messages, std::string keyword, std::string sender) {
    std::vector<Message*> results;
    for (auto msg : messages) {
        if (msg->getSender() == sender && msg->getContent().find(keyword) != std::string::npos) {
            results.push_back(msg);
        }
    }
    return results;
}