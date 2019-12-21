#include "DescriptionManager.h"

DescriptionManager::DescriptionManager(std::string n, std::string ob, std::string t, std::string sf, std::string c)
{
	name = n;
	objective = ob;
	tasks = t;
	subjectField = sf;
	client = c;
}

void DescriptionManager::setName(std::string n)
{
	name = n;
}

void DescriptionManager::setObjective(std::string ob)
{
	objective = ob;
}

void DescriptionManager::setTasks(std::string t)
{
	tasks = t;
}

void DescriptionManager::setSubjectField(std::string sf)
{
	subjectField = sf;
}

void DescriptionManager::setClient(std::string c)
{
	client = c;
}

void DescriptionManager::addPrerequisites(std::string pr)
{
	while (pr.find(",") != std::string::npos)
	{
		Prerequisites.push_back(pr.substr(0,pr.find(",")));
		pr.substr(pr.find(",") + 1);
	}
	Prerequisites.push_back(pr);
}

std::string DescriptionManager::getName()
{
	return name;
}

std::string DescriptionManager::getObjective()
{
	return objective;
}

std::string DescriptionManager::getTasks()
{
	return tasks;
}

std::string DescriptionManager::getSubjectField()
{
	return subjectField;
}

std::string DescriptionManager::getClient()
{
	return client;
}

std::vector<std::string> DescriptionManager::getPrerequisites()
{
	return Prerequisites;
}