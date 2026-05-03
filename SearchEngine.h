#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "Message.h"
#include <vector>
#include <string>
#include <memory>

/// @brief Search utility to find messages.
/// Demonstrates function overloading (compile-time polymorphism).
class SearchEngine {
public:
    SearchEngine() = default;
    ~SearchEngine() = default;

    // Overloaded search methods
    // Returns a vector of non-owning const raw pointers to the found messages.
    std::vector<const Message*> search(const std::vector<std::unique_ptr<Message>>& messages, const std::string& keyword) const;
    std::vector<const Message*> search(const std::vector<std::unique_ptr<Message>>& messages, const std::string& keyword, const std::string& sender) const;
};

#endif // SEARCHENGINE_H