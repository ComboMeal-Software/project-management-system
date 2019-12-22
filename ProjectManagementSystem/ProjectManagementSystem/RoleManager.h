#pragma once
#pragma once
#ifndef ROLEMANAGER_H
#define ROLEMANAGER_H

#include <string>
#include <map>

class User;

class RoleManager
{
private:
	User* initiator;
	User* manager;
	std::map<std::string, User*> participants;
public:
	RoleManager(User* init);
	void setManager(User* mngr);
	void addParticipant(User* part);
	User* getInitiator();
	User* getManager();
	std::map<std::string, User*> getParticipants();
	void removeParticipant(std::string name);
};

#endif