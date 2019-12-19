// This is the DeadlineManager composition class declaration for the Project classes
#pragma once
#ifndef DEADLINEMANAGER_H
#define DEADLINEMANAGER_H

#include <string>

class DeadlineManager
{
private:
	unsigned char day;
	unsigned char month;
	unsigned short year;
public:
	DeadlineManager(std::string date);
	~DeadlineManager();
	void editDeadline(std::string date);
	std::string getDeadline();
};

#endif