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

class User {
private:

	// Private fields

	std::string name;
	std::string password;
	int freetime;
	std::map<std::string, Project*> currentProjects;
	std::map<std::string, Project*> finishedProjects;
	NotificationManager notifications;
	std::vector<float> rating;
	std::vector<std::string> prerequisites;
	std::vector<std::string> StudyFields;

	// Private methods
	void setName(std::string name); //UserInfoManager >
	void changeFreetime(int time);
	void addCurrentProjects(Project& project);
	void addFinishedProjects(Project& project);
	void addPrerequisites(std::string prerequisite);
	void addStudyFields(std::string StudyFields); // < UserInfoManager

public:

	// Public methods

	User(std::string name, std::string password, int free_time, std::string prerequisites, std::string StudyFields);
	void addNewNotification(Notification notification);
	std::string getName();
	int getFreetime();
	float getRating(); //sum % vector length
	std::map<std::string, Project*> getCurrentProjects();
	std::map<std::string, Project*> getFinishedProjects();
	std::vector<std::string> getPrerequisites();
	bool checkPassword(std::string pass);
	void changeInfo(); // UserInfoManager
	void checkNotifications(); //
	void checkNewProjects();
	void checkCurrentProjects();
	void displayFinishedProjects(); // needed or not? seems like an interface thing, we already got getFinishedProjects
	void findNewProjects();
	void applyToNewProjects(Project* activeProject);
	void workOnProject(Project* activeProject);
	void collectRating(float newRating);
	void createProject();
	~User();
	friend std::ostream& operator<<(std::ostream &out, const User &user);
};


#endif // !USERCLASS_H
