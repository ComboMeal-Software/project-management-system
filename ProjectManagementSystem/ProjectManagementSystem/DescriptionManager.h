#pragma once
#ifndef DESCRIPTIONMANAGER_H
#define DESCRIPTIONMANAGER_H

#include <string>
#include <vector>

class DescriptionManager
{
private:
	std::string name;
	std::string objective;
	std::string tasks;
	std::string subjectField;
	std::string client;
	std::vector<std::string> Prerequisites;
public:
	DescriptionManager(std::string n, std::string ob, std::string t, std::string sf, std::string c);
	~DescriptionManager() {};
	void setName(std::string n);
	void setObjective(std::string ob);
	void setTasks(std::string t);
	void setSubjectField(std::string sf);
	void setClient(std::string c);
	void addPrerequisites(std::string pr);
	std::string getName();
	std::string getObjective();
	std::string getTasks();
	std::string getSubjectField();
	std::string getClient();
	std::vector<std::string> getPrerequisites();
};

#endif