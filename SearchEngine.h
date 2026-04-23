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

    // Methods
    std::vector<Message*> searchByKeyword(std::vector<Message*> messages, std::string keyword);
    std::vector<Message*> searchBySender(std::vector<Message*> messages, std::string sender);
    std::vector<Message*> searchByDate(std::vector<Message*> messages, std::string date);
};

#endif