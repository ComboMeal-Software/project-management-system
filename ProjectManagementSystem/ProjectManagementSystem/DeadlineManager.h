// This is the DeadlineManager composition class declaration for the Project classes
#pragma once
#ifndef DEADLINEMANAGER_H
#define DEADLINEMANAGER_H

#include <string>

class DeadlineManager
{
private:
	std::string date;
	unsigned char day;
	unsigned char month;
	unsigned short year;
	void stringToDate(std::string dt);
public:
	DeadlineManager(std::string dt);
	~DeadlineManager() {};
	void setDeadline(std::string dt);
	std::string getDeadline();
	int getDeadlineDay();
	int getDeadlineMonth();
	int getDeadlineYear();
};

#endif