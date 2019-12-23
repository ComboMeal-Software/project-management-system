#include "Interface.h"

#include "UserClass.h"
#include "ProjectClass.h"

Interface::~Interface()
{
	for (std::map<std::string, std::vector<std::string>>::iterator itr = commands.begin(); itr != commands.end(); itr++)
	{
		itr->second.clear();
	}
	commands.clear();
}