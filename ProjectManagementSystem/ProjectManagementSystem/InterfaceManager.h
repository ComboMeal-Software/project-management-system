#pragma once
#ifndef InterfaceManager_H
#define InterfaceManager_H

#include <vector>
#include <string>
#include <map>

struct Notification;
class User;
class Project;
class Database;

class InterfaceManager
{
private:
	Database* database;
	User* currentUser;
	std::map<std::string, std::vector<std::string>> commands;
	std::string status;
	std::string input;
	void editProject(std::string name);
public:
	InterfaceManager();
	void init();
	void welcome();
	void registerUser(std::string name, std::string password);
	void login(std::string name, std::string password);
	void logout();
	void help();
	void editInfo();
	void displayNotification(Notification notification);
	void checkNotifications();
	void createProject();
	void findProjects();
	void displayProjects();
	~InterfaceManager();
};

#endif