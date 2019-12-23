#include "NotificationManager.h"
#include "NotificationStruct.h"
#include "Interface.h"
#include "ProjectClass.h"
#include <iostream>
#include <vector>

NotificationManager::NotificationManager(User* us){

	user = us;

}
std::vector<Notification> NotificationManager::getNewNots() {

	return new_notifications;

}

void NotificationManager::deleteNotification(int i) {

	new_notifications.erase(i);

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

	delete user;

}
//void NotificationManager::reactNotification(int i, std::string command) {
//	
//	switch (type)
//	{
//	case message:
//		if (command == "mark_as_seen"){
//
//			new_notifications.erase(i);
//			break;
//
//		}
//		else
//			break;
//
//	case invitation:
//		if (command == "accept") {
//			
//			Project* project = database->getProject(new_notifications[i].project);
//			project->addParticipant(user);
//			delete project;
//			new_notifications.erase(i);
//			break;
//
//		}
//		else if (command == "decline"){
//
//			new_notifications.erase(i);
//			break;
//
//		}
//		else
//			break;
//
//	case rating:
//
//		if (command == "yes") {
//
//		}
//		else if (command == "no") {
//
//			new_notifications.erase(i);
//			break;
//
//		}
//		else
//			break;
//
//	default:
//
//		break;
//	}
//
//}