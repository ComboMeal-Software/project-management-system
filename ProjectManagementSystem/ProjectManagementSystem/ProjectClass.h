// Project Class header file
// It contains the abstract class and two derived Project classes (Mandatory and Optional)

#pragma once
#ifndef PROJECTCLASS_H
#define PROJECTCLASS_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

class DeadlineManager;
class DescriptionManager;
class RoleManager;
class StatusManager;
class User;

class Project //Abstract
{
private:
	DeadlineManager* deadline;
	DescriptionManager *description;
	RoleManager *roles;
	StatusManager *statusIndicator;
public:
	Project(User* initiator, std::string name, std::string objective, std::string tasks, std::string subjectField, std::string client, std::string dl, std::string prerequisites);
	void addParticipant(User *participant);
	void setManager(User* mngr);
	//void editInfo(); // It's an interface thing so it probably should just be a friend or something
	void removeParticipant(std::string name);
	User* getInitiator();
	User* getManager();
	std::map<std::string, User*> getParticipants();
	std::string getSubjectField();
	std::string getName();
	unsigned char getDeadlineDay();
	unsigned char getDeadlineMonth();
	unsigned short getDeadlineYear();
	std::string getObjective();
	std::string getStatus();
	void setSubjectField(std::string subjectField);
	void setDeadline(std::string dl);
	void setStatus(std::string status);
	void setObjective(std::string objective);
	void setTasks(std::string objective);
	void setPrerequisites(std::string prerequisites);
	void setClient(std::string client);
	std::vector<std::string> getPrerequisites();
	friend std::ostream& operator<<(std::ostream& os, const Project& pr);
	~Project();
};

#endif