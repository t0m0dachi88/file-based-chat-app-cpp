#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include <ctime>

// Abstract base class for Message
class Message {
protected:
    std::string sender;
    std::string content;
    std::string timestamp;
    bool isRead;

public:
    // Constructor
    Message(std::string s, std::string c);

    // Pure virtual destructor
    virtual ~Message() = 0;

    // Pure virtual methods
    virtual void display() = 0;
    virtual std::string getType() = 0;

    // Getters
    std::string getSender() const { return sender; }
    std::string getContent() const { return content; }
    std::string getTimestamp() const { return timestamp; }
    bool getIsRead() const { return isRead; }

    // Setters
    void setIsRead(bool r) { isRead = r; }

    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Message& m);
};

#endif