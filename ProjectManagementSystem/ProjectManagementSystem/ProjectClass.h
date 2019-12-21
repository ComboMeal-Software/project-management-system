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
	RoleManager* roles;
	StatusManager *statusIndicator;
	// --Private methods--
	virtual void addParticipant(User &participant) = 0; //Pure virtual method!
public:
	void findParticipants();
	void editInfo();
	User* getInitiator();
	User* getManager();
	std::map<std::string, User*> getParticipants();
	std::string getSubjectField();
	std::string getName();
	std::string getDeadlineDay();
	std::string getDeadlineMonth();
	std::string getDeadlineYear();
	std::string getStatus();
	std::vector<std::string> getPrerequisites();
	friend std::ostream& operator<<(std::ostream& os, const Project& pr);
};

class MandatoryProject : Project {
private:
	void addParticipant(User &participant);
public:
	MandatoryProject(User &initiator, std::string name, std::string objective, std::string tasks, std::string subjectField, std::string deadline, std::string prerequisites);
	~MandatoryProject(); //Gotta work on this
};

class OptionalProject : Project {
private:
	void addParticipant(User &participant);
public:
	OptionalProject(User &initiator, std::string name, std::string objective, std::string tasks, std::string subjectField, std::string deadline, std::string prerequisites);
	~OptionalProject(); //Gotta work on this
};

#endif