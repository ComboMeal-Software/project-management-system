// Notification Struct file

#pragma once
#ifndef NOTIFICATIONSTRUCT_H
#define NOTIFICATIONSTRUCT_H

#include <iostream>
#include <string>
#include <map>

class User;

enum nType { message, invitation, rating, notify };
struct Notification {
	
	nType type;
	std::string text;
	std::string sender;
	std::string project;
	std::map<std::string, User*> participants;

	Notification( nType type, std::string text, std::string sender, std::string project );
	Notification(nType type, std::string text, std::string sender, std::map<std::string, User*> participants);
};

#endif // !NOTIFICATIONSTRUCT_H
