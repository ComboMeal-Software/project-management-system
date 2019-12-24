// User Class header file
//

#pragma once
#ifndef USERCLASS_H
#define USERCLASS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Notification;
class Project;
class NotificationManager;
class UserInfoManager;
class RatingManager;

class User {
private:

	// Private fields
  
	NotificationManager* notifications;
	UserInfoManager* infoManager;
	RatingManager* ratingManager;

public:

	// Public methods

	User(std::string name, std::string password, int free_time, std::string prerequisites, std::string StudyFields);
	std::string getName();
	int getFreetime();
	float getRating();
	std::map<std::string, Project*> getCurrentProjects();
	std::map<std::string, Project*> getFinishedProjects();
	std::vector<std::string> getPrerequisites();
	std::vector<std::string> getStudyFields();
	void addProject(Project* project);
	bool checkPassword(std::string pass);
	void changeInfo(int i, std::string input); // UserInfoManager to be done!!!
	void collectRating(float newRating);
	void deleteProject(std::string name);
	int checkNotifications();
	std::vector<Notification> extractNotifications();
	void returnNotifications(std::vector<Notification> returned);
	void addNewNotification(Notification notification);
	
	~User();
	friend std::ostream& operator<<(std::ostream& os, const User& user);
};


#endif // !USERCLASS_H
