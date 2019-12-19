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
class StatusManager;
class User;

class Project //Abstract
{
private:
	DescriptionManager *description;
	vector<std::string> Prerequisites;
	StatusManager *statusIndicator;
	DeadlineManager *deadline;
	User *initiator;
	User *manager;
	map<std::string, User*> participants;
	// --Private methods--
	void setStatus(std::string status);
	void setManager(User &client);
	void setDeadline(std::string deadline);
	void addPrerequisites(std::string prerequisites);
	virtual void addParticipant(User &participant) = 0; //Pure virtual method!
public:
	void findParticipants();
	void editInfo();
	User* getInitiator();
	std::string getClient();
	User* getManager();
	map<std::string, User*> participants;
	std::string getSubjectField();
	std::string getName();
	std::string getObjective();
	std::string getTasks();
	std::string getDeadline();
	vector<std::string> getPrerequisites();
	std::string getStatus();
	friend ostream& operator<<(ostream& os, const Project& pr);
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