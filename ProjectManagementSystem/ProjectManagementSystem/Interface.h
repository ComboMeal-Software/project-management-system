#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <string>
#include <map>

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
public:
	Interface();
	void createProject();
	~Interface();
};

#endif