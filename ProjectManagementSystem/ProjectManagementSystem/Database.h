#pragma once
#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <map>

class User;
class Project;

class Database
{
private:
	std::map<std::string, User*> users;
	std::map<std::string, Project*> projects;
	std::map<std::string, Project*> finishedProjects;
public:
	void createUser(std::string name, std::string password, int free_time, std::string prerequisites, std::string StudyFields);
	void createProject(User* initiator, std::string name, std::string objective, std::string tasks, std::string subjectField, std::string client, std::string deadline, std::string prerequisites);
	User* getUser(std::string name);
	std::vector<User*> findParticipants(std::vector<std::string> prer);
	std::vector<Project*> findProjects(std::vector<std::string> prer);
	void deleteUser(std::string userName);
	void deleteProject(std::string projectName);
	void finishProject(std::string projectName);
};

#endif