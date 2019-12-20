#pragma once
#ifndef STATUSMANAGER_H
#define STATUSMANAGER_H

#include <string>

enum Status { Initialization, Recruitment, Active, Closed };
static const std::string StatusStrings[] = { "Initialization", "Recruitment", "Active", "Closed"};

class StatusManager
{
private:
	enum Status Indicator = Initialization;
public:
	StatusManager(){};
	~StatusManager(){};
	void setStatus(std::string status);
	std::string getStatus();
};

#endif