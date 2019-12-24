#include <iostream>
#include <map>
#include <vector>
#include "ProjectClass.h"

#include "DeadlineManager.h"
#include "DescriptionManager.h"
#include "RoleManager.h"
#include "StatusManager.h"
#include "UserClass.h"


void Project::addParticipant(User* participant)
{
	roles->addParticipant(participant);
}

void Project::setManager(User* mngr)
{
	roles->setManager(mngr);
}

void Project::removeParticipant(std::string name)
{
	roles->removeParticipant(name);
}

User* Project::getInitiator()
{
	return roles->getInitiator();
}

User* Project::getManager()
{
	return roles->getManager();
}

std::map<std::string, User*> Project::getParticipants()
{
	return roles->getParticipants();
}

std::string Project::getSubjectField()
{
	return description->getSubjectField();
}

std::string Project::getName()
{
	return description->getName();
}

std::string Project::getObjective()
{
	return description->getObjective();
}

unsigned char Project::getDeadlineDay()
{
	return deadline->getDeadlineDay();
}

unsigned char Project::getDeadlineMonth()
{
	return deadline->getDeadlineMonth();
}

unsigned short Project::getDeadlineYear()
{
	return deadline->getDeadlineYear();
}

std::vector<std::string> Project::getPrerequisites()
{
	return description->getPrerequisites();
}

std::string Project::getStatus()
{
	return statusIndicator->getStatus();
}

void Project::setClient(std::string client)
{
	description->setClient(client);
}

void Project::setDeadline(std::string dl)
{
	deadline->setDeadline(dl);
}

void Project::setObjective(std::string objective)
{
	description->setObjective(objective);
}

void Project::setPrerequisites(std::string prer)
{
	description->setPrerequisites(prer);
}

void Project::setStatus(std::string status)
{
	statusIndicator->setStatus(status);
}

void Project::setSubjectField(std::string subjectField)
{
	description->setSubjectField(subjectField);
}

void Project::setTasks(std::string tasks)
{
	description->setTasks(tasks);
}

std::ostream& operator<<(std::ostream& os, const Project& pr)
{
	os << "Проект " << pr.description->getName() << std::endl;
	os << "Статус: " << pr.statusIndicator->getStatus() << std::endl;
	os << "Цель - " << pr.description->getObjective() << std::endl;
	os << "Задачи: " << pr.description->getTasks() << std::endl;
	os << "Предметная область - " << pr.description->getSubjectField() << std::endl;
	os << "Заказчик - " << pr.description->getClient() << std::endl;
	os << "Необходимые навыки: ";
	std::vector<std::string> temp = pr.description->getPrerequisites();
	for (int i = 0; i < temp.size() - 1; i++)
	{
		os << temp[i] << ", ";
	}
	os << temp[temp.size() - 1];
	os << std::endl;
	os << "Дедлайн - " << pr.deadline->getDeadline() << std::endl;
	os << "Люди:" << std::endl;
	os << "Инициатор - " << pr.roles->getInitiator()->getName() << std::endl;
	if(pr.roles->getManager() != NULL)
		os << "Менеджер - " << pr.roles->getManager()->getName() << std::endl;
	os << "Участники: ";
	std::map<std::string, User*> mtemp = pr.roles->getParticipants();
	for (const std::pair<std::string, User*>& p : mtemp)
	{
		os << p.first << ", ";
	}
	os << std::endl;
	return os;
}

Project::Project(User* initiator, std::string name, std::string objective, std::string tasks, std::string subjectField, std::string client, std::string dl, std::string prerequisites)
{
	deadline = new DeadlineManager(dl);
	description = new DescriptionManager(name, objective, tasks, subjectField, client, prerequisites);
	roles = new RoleManager(initiator);
	statusIndicator = new StatusManager();
}

Project::~Project()
{
	std::map<std::string, User*> tempm = roles->getParticipants();
	tempm.insert(std::pair<std::string, User*>(roles->getInitiator()->getName(), roles->getInitiator()));
	tempm.insert(std::pair<std::string, User*>(roles->getManager()->getName(), roles->getManager()));
	for (const std::pair<std::string, User*>& p : tempm)
	{
		p.second->deleteProject(description->getName());
	}
	delete deadline;
	delete description;
	delete statusIndicator;
	delete roles;
}