// Notification Struct file

#pragma once
#ifndef NOTIFICATIONSTRUCT_H
#define NOTIFICATIONSTRUCT_H

#include <iostream>
#include <string>

enum nType { message, invitation, rating, notify};
struct Notification {
	
	nType type;
	std::string text;
	std::string sender;
	std::string project;

	Notification(nType type, std::string text, std::string sender, std::string project);

};

#endif // !NOTIFICATIONSTRUCT_H
