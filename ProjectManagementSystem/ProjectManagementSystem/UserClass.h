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
	bool checkPassword(std::string pass);
	void changeInfo(); // UserInfoManager
	void collectRating(float newRating);
	void deleteProject(std::string name);

	void addNewNotification(Notification notification);
	void checkNotifications();
	void checkNewProjects();
	void checkCurrentProjects();
	void displayFinishedProjects(); // needed or not? seems like an interface thing, we already got getFinishedProjects
	void findNewProjects();
	void applyToNewProjects(Project* activeProject);
	void workOnProject(Project* activeProject);
	void createProject();
	~User();
	friend std::ostream& operator<<(std::ostream& os, const User& user);
};


#endif // !USERCLASS_H
