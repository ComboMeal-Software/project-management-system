#include <iostream>
#include <map>
#include <vector>
#include "ProjectClass.h"

#include "DeadlineManager.h"
#include "DescriptionManager.h"
#include "RoleManager.h"
#include "StatusManager.h"
//#include "User.h"

void Project::findParticipants()
{

}

void Project::editInfo()
{

}

User* Project::getInitiator()
{
	roles->getInitiator();
}

User* Project::getManager()
{
	roles->getManager();
}

std::map<std::string, User*> Project::getParticipants()
{
	roles->getParticipants();
}

std::string Project::getSubjectField()
{
	description->getSubjectField();
}

std::string Project::getName()
{
	description->getName();
}

std::string Project::getDeadlineDay()
{
	deadline->getDeadlineDay();
}

std::string Project::getDeadlineMonth()
{
	deadline->getDeadlineMonth();
}

std::string Project::getDeadlineYear()
{
	deadline->getDeadlineYear();
}

std::vector<std::string> Project::getPrerequisites()
{
	description->getPrerequisites();
}

std::string Project::getStatus()
{
	statusIndicator->getStatus();
}

std::ostream& operator<<(std::ostream& os, const Project& pr)
{
	os << "Project " << pr.description->getName() << std::endl;
	os << "Status: " << pr.statusIndicator->getStatus() << std::endl;
	os << "Objective - " << pr.description->getObjective() << std::endl;
	os << "Tasks: " << pr.description->getTasks() << std::endl;
	os << "Subject Field - " << pr.description->getSubjectField() << std::endl;
	os << "Client - " << pr.description->getClient() << std::endl;
	os << "Prerequisites: ";
	std::vector<std::string> *temp = &pr.description->getPrerequisites();
	for (int i = 0; i < temp->size(); i++)
	{
		os << temp->operator[](i) << " ";
	}
	os << std::endl;
	os << "Deadline - " << pr.deadline->getDeadline() << std::endl;
	os << "People:" << std::endl;
	//os << "Initiator - " << pr.roles->getInitiator()->getName() << std::endl;
	//os << "Manager - " << pr.roles->getManager()->getName() << std::endl;
	os << "Participants: ";
	std::map<std::string, User*>* mtemp = &pr.roles->getParticipants();
	for (const std::pair<std::string, User*>& p : mtemp->begin)
	{
		os << p.first << ", ";
	}
	os << std::endl;
}

MandatoryProject::MandatoryProject(User& initiator, std::string name, std::string objective, std::string tasks, std::string subjectField, std::string client, std::string dl, std::string prerequisites)
{
	deadline = new DeadlineManager(dl);
	description = new DescriptionManager(name, objective, tasks, subjectField, client, prerequisites);
	roles = new RoleManager(initiator);
	statusIndicator = new StatusManager();
}

OptionalProject::OptionalProject(User& initiator, std::string name, std::string objective, std::string tasks, std::string subjectField, std::string client, std::string dl, std::string prerequisites)
{
	deadline = new DeadlineManager(dl);
	description = new DescriptionManager(name, objective, tasks, subjectField, client, prerequisites);
	roles = new RoleManager(initiator);
	statusIndicator = new StatusManager();
}

void MandatoryProject::addParticipant(User& participant)
{
	//Got an idea here! Gonna describe it on GitHub.
}

void OptionalProject::addParticipant(User& participant)
{
	//Got an idea here! Gonna describe it on GitHub.
}