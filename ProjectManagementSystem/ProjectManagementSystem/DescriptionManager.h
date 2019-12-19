#pragma once
#ifndef DESCRIPTIONMANAGER_H
#define DESCRIPTIONMANAGER_H

#include <string>

class DescriptionManager
{
private:
	std::string name;
	std::string objective;
	std::string tasks;
	std::string subjectField;
	std::string client;
public:
	DescriptionManager(std::string name, std::string objective, std::string tasks, std::string subjectField, std::string client);
	~DescriptionManager();
	void setName(std::string name);
	void setObjective(std::string objective);
	void setTasks(std::string tasks);
	void setSubjectField(std::string subjectField);
	void setClient(std::string client);
	std::string getName();
	std::string getObjective();
	std::string getTasks();
	std::string getSubjectField();
	std::string getClient();
};

#endif