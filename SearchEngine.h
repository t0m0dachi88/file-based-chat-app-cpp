#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "Message.h"
#include <vector>
#include <string>

class SearchEngine {
public:
    // Constructor
    SearchEngine();

    // Destructor
    ~SearchEngine();

    // Overloaded search methods (FIX 6: Compile-time polymorphism)
    // FIX 4: Pass-by-value inefficiency fixed (using const reference)
    std::vector<Message*> search(const std::vector<Message*>& messages, std::string keyword);
    std::vector<Message*> search(const std::vector<Message*>& messages, std::string keyword, std::string sender);
};

#endif