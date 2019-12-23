#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <string>
#include <map>

struct Notification;
class User;
class Project;
class Database;

class Interface
{
private:
	Database* database;
	User* currentUser;
	std::map<std::string, std::vector<std::string>> commands;
	std::string status;
	std::string input;
	void editProject(std::string name);
public:
	Interface();
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
	~Interface();
};

#endif