#include "NotificationManager.h"
#include "NotificationStruct.h"
#include "Interface.h"

#include <iostream>
#include <vector>

std::vector<Notification> NotificationManager::getNewNots() {

	return new_notifications;

}

void NotificationManager::addNotification(Notification notification) {

	new_notifications.push_back(notification);

}

int NotificationManager::checkNotifications() {

	return new_notifications.size();

}

void NotificationManager::reactNotification(int i, std::string command) {

	nType type = new_notifications[i].type
	switch (type)
	{
	case message:
		if (command == "mark_as_seen"){

			new_notifications.erase(i); // опнакелю
			break;

		}
		else
			break;

	case invitation:

		break;

	case rating:

		break;

	default:

		break;
	}

}