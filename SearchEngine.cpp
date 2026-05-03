#include "SearchEngine.h"

// --- Search by keyword ---
std::vector<const Message*> SearchEngine::search(const std::vector<std::unique_ptr<Message>>& messages, const std::string& keyword) const {
    std::vector<const Message*> results;
    for (const auto& msg : messages) {
        if (msg->getContent().find(keyword) != std::string::npos) {
            results.push_back(msg.get());
        }
    }
    return results;
}

// --- Search by keyword and sender ---
std::vector<const Message*> SearchEngine::search(const std::vector<std::unique_ptr<Message>>& messages, const std::string& keyword, const std::string& sender) const {
    std::vector<const Message*> results;
    for (const auto& msg : messages) {
        if (msg->getSender() == sender && msg->getContent().find(keyword) != std::string::npos) {
            results.push_back(msg.get());
        }
    }
    return results;
}