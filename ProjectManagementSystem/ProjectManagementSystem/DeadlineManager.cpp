#include "DeadlineManager.h"

void DeadlineManager::stringToDate(std::string dt)
{
	day = stoi(dt.substr(dt.find("/") - 2, 2));
	dt = dt.substr(dt.find("/") + 1);
	month = stoi(dt.substr(dt.find("/") - 2, 2));
	dt = dt.substr(dt.find("/") + 1);
	year= stoi(dt.substr(dt.find("/") - 2, 2));
}

DeadlineManager::DeadlineManager(std::string dt)
{
	date = dt;
	stringToDate(dt);
}

void DeadlineManager::setDeadline(std::string dt)
{
	date = dt;
	stringToDate(dt);
}

std::string DeadlineManager::getDeadline()
{
	return date;
}

int DeadlineManager::getDeadlineDay()
{
	return day;
}

int DeadlineManager::getDeadlineMonth()
{
	return month;
}

int DeadlineManager::getDeadlineYear()
{
	return year;
}
