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
	void deleteNotification(int i);
	void updateNotifications(std::vector<Notification>);
	void addNotification(Notification notification);
	int checkNotifications();
	~NotificationManager();

};

#endif // !NOTIFICATIONMANAGERCLASS_H
