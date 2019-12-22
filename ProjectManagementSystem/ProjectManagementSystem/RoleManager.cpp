#include "RoleManager.h"
#include "UserClass.h"

RoleManager::RoleManager(User& init)
{
	initiator = &init;
}

void RoleManager::setManager(User& mngr)
{
	manager = &mngr;
}

void RoleManager::addParticipant(User& part)
{
	participants.insert({ part.getName, &part });
}

User* RoleManager::getInitiator()
{
	return initiator;
}

User* RoleManager::getManager()
{
	return manager;
}

std::map<std::string, User*> RoleManager::getParticipants()
{
	return participants;
}