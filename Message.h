#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>

/// @brief Abstract base class for messages. Demonstrates inheritance, pure virtual
/// functions, operator overloading, and robust access control.
class Message {
protected:
    std::string sender_;
    std::string content_;
    std::string timestamp_;
    bool isRead_;

public:
    // Constructor
    Message(const std::string& sender, const std::string& content);

    // Pure virtual destructor
    virtual ~Message() = 0;

    // Pure virtual methods
    virtual void display() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getContent() const { return content_; }

    // --- Getters ---
    const std::string& getSender() const { return sender_; }
    const std::string& getTimestamp() const { return timestamp_; }
    bool getIsRead() const { return isRead_; }

    // --- Setters ---
    void setIsRead(bool isRead) { isRead_ = isRead; }
    void setTimestamp(const std::string& timestamp) { timestamp_ = timestamp; }

    // Operator overloading for standard message output
    friend std::ostream& operator<<(std::ostream& os, const Message& msg);
};

#endif // MESSAGE_H