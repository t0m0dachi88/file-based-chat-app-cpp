#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <queue>
#include <string>

class NotificationManager {
private:
    std::queue<std::string> notifications; // STL queue

public:
    // Constructor
    NotificationManager();

    // Destructor
    ~NotificationManager();

    // Methods
    void addNotification(std::string msg);
    void displayNotifications();
    int getCount();
};

#endif