#include "Interface.h"

#include "UserClass.h"
#include "ProjectClass.h"
#include "Database.h"

Interface::Interface()
{
	database = new Database();
	currentUser = NULL;
	commands = {
		{"start", {"register [name] [password]", "login [name] [password"}},
		{"logged_in",{"create_project", "my_projects", "edit_info", "check_notifications"}}
	};
}

void Interface::createProject()
{
	std::string name;
	std::string objective;
	std::string tasks;
	std::string subjectField;
	std::string client;
	std::string deadline;
	std::string prerequisites;
	std::cout << "Введите информацию о создаваемом проекте. В дальнейшем информация может быть изменена.";
	std::cout << "Back - выйти";
}

Interface::~Interface()
{
	for (std::map<std::string, std::vector<std::string>>::iterator itr = commands.begin(); itr != commands.end(); itr++)
	{
		itr->second.clear();
	}
	commands.clear();
}