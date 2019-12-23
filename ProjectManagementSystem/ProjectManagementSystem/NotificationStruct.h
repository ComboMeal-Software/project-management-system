// Notification Struct file

#pragma once
#ifndef NOTIFICATIONSTRUCT_H
#define NOTIFICATIONSTRUCT_H

#include <iostream>
#include <string>

enum nType { message, invitation, rating };
struct Notification {
	
	nType type;
	std::string text;
	std::string sender;
	std::string receiver;

	Notification( nType type, std::string text, std::string sender, std::string receiver );

};

#endif // !NOTIFICATIONSTRUCT_H
