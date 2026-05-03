#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include "Message.h"
#include <vector>
#include <string>
#include <memory>

/// @brief Represents a private chat between two users.
/// Demonstrates proper memory management using std::unique_ptr.
class PrivateChat {
private:
    std::string id_;
    std::string user1_;
    std::string user2_;
    
    // Using std::unique_ptr to completely eliminate memory leaks from dangling raw pointers
    std::vector<std::unique_ptr<Message>> messages_; 

public:
    // Constructor
    PrivateChat(const std::string& user1, const std::string& user2);

    // Destructor
    ~PrivateChat() = default; // unique_ptr automatically cleans up

    // Methods
    void addMessage(std::unique_ptr<Message> msg); // Renamed from sendMessage for clarity
    void viewHistory() const;
    void markAsRead();
    int getUnreadCount() const;

    // --- Getters ---
    const std::string& getId() const { return id_; }
    const std::string& getUser1() const { return user1_; }
    const std::string& getUser2() const { return user2_; }
    
    // Return const reference to vector to avoid copying
    const std::vector<std::unique_ptr<Message>>& getMessages() const { return messages_; }
};

#endif // PRIVATECHAT_H