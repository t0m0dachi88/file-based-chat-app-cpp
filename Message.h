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
    virtual std::string getContent() const { return content; } // FIX: Virtual to allow overriding
    std::string getTimestamp() const { return timestamp; }
    bool getIsRead() const { return isRead; }

    // Setters
    void setIsRead(bool r) { isRead = r; }
    void setTimestamp(const std::string& ts) { timestamp = ts; } // FIX 1: Timestamp setter

    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Message& m);
};

#endif