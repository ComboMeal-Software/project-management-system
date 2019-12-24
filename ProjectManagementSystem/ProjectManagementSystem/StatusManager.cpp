#include "StatusManager.h"

std::string StatusManager::getStatus()
{
	return StatusStrings[Indicator];
}

void StatusManager::setStatus(std::string status)
{
	for (int i = 0; i < 5; i++) {
		if (StatusStrings[i] == status)
		{
			Indicator = static_cast<Status>(i);
			break;
		}
	}
	// An error message can be added here like "Woah! There's no such status!". Yeah... Can't be bothered B)
}