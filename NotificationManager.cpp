#include "NotificationManager.h"
#include <iostream>

// Constructor
NotificationManager::NotificationManager() {}

// Destructor
NotificationManager::~NotificationManager() {}

// Add notification
void NotificationManager::addNotification(std::string msg) {
    notifications.push(msg);
}

// Display notifications
void NotificationManager::displayNotifications() {
    while (!notifications.empty()) {
        std::cout << "Notification: " << notifications.front() << std::endl;
        notifications.pop();
    }
}

// Get count
int NotificationManager::getCount() {
    return notifications.size();
}