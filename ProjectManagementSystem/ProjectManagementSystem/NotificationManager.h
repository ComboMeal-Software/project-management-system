// NotificationManager Class file 

#pragma once
#ifndef NOTIFICATIONMANAGERCLASS_H
#define NOTIFICATIONMANAGERCLASS_H

#include <iostream>
#include <vector>

struct Notification;

class NotificationManager {

private:
	std::vector<Notification> new_notifications;

public:
	NotificationManager();
	std::vector<Notification> getNewNots();
	void addNotification(Notification notification);
	int checkNotifications();
	void reactNotification(int i, std::string command);
	~NotificationManager();

};

#endif // !NOTIFICATIONMANAGERCLASS_H
