#include "NotificationManager.h"
#include "NotificationStruct.h"
#include "Interface.h"
#include "ProjectClass.h"
#include <iostream>
#include <vector>

NotificationManager::NotificationManager(){

}
std::vector<Notification> NotificationManager::getNewNots() {

	return new_notifications;

}

void NotificationManager::deleteNotification(int i) {

	new_notifications.erase(new_notifications.begin()+i);

}

void NotificationManager::updateNotifications(std::vector<Notification> returned) {

	new_notifications.clear();
	new_notifications = returned;

}

void NotificationManager::addNotification(Notification notification) {

	new_notifications.push_back(notification);

}

int NotificationManager::checkNotifications() {

	return new_notifications.size();

}

NotificationManager::~NotificationManager() {


}