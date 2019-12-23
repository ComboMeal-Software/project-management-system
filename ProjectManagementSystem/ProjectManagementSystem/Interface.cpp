#include "Interface.h"

#include "UserClass.h"
#include "ProjectClass.h"
#include "Database.h"
#include "NotificationStruct.h"

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
	std::cout << "Введите информацию о создаваемом проекте. В дальнейшем информация может быть изменена." << std::endl;
	std::cout << "Выйти - back" << std::endl;
	std::cout << "Имя проекта: ";
	std::getline(std::cin, name);
	if (name == "back")
		return;
	std::cout << std::endl;
	std::cout << "Цель проекта: ";
	std::getline(std::cin, objective);
	if (objective == "back")
		return;
	std::cout << std::endl;
	std::cout << "Задачи: ";
	std::getline(std::cin, tasks);
	if (tasks == "back")
		return;
	std::cout << std::endl;
	std::cout << "Предметная область: ";
	std::getline(std::cin, subjectField);
	if (subjectField == "back")
		return;
	std::cout << std::endl;
	std::cout << "Заказчик: ";
	std::getline(std::cin, client);
	if (client == "back")
		return;
	std::cout << std::endl;
	std::cout << "Дедлайн (дд/мм/гггг): ";
	std::getline(std::cin, deadline);
	if (deadline == "back")
		return;
	std::cout << std::endl;
	std::cout << "Необходимые навыки: ";
	std::getline(std::cin, prerequisites);
	if (prerequisites == "back")
		return;
	std::cout << std::endl;
	database->createProject(currentUser, name, objective, tasks, subjectField, client, deadline, prerequisites);
	std::cout << "Проект " << name << " создан успешно" << std::endl;
	return;
}

void Interface::findProjects()
{
	std::string input;
	std::cout << "Выйти - back";
	std::vector<Project*> *temp = &(database->findProjects(currentUser->getPrerequisites()));
	std::cout << "Подходящие вам проекты:" << std::endl;
	if (temp->size() == 0)
	{
		std::cout << "Подходящие проекты отсутсвуют" << std::endl;
		return;
	}
	for (int i = 0; i < temp->size(); i++)
	{
		std::cout << i << " " << temp->operator[](i)->getName() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Введите номер проекта, чтобы показать подробную информацию." << std::endl;
	std::cout << "apply [number] - подать заявку на участие в проекте";
	while (true)
	{
		std::cin >> input;
		if (input == "apply")
		{
			std::cin >> input;
			std::string message;
			std::cout << "Введите ваше сообщение." << std::endl;
			std::getline(std::cin, message);
			Notification tempn = Notification(notify, message, currentUser->getName(), temp->operator[](std::stoi(input))->getName());
			temp->operator[](std::stoi(input))->getInitiator()->addNewNotification(tempn);
			break;
		}
		else
			if (input == "back")
				break;
			else
			{
				std::cout << temp->operator[](std::stoi(input));
			}
	}
	return;
}

void Interface::displayProjects()
{
	std::map<std::string, Project*>* temp = &(currentUser->getCurrentProjects());
	std::cout << "Вы состоите в следующих проектах: " << std::endl;
	for (const std::pair<std::string, Project*>& p : temp->begin)
	{
		std::cout << p.first << " " << p.second->getName();
	}
	std::cout << "Введите номер проекта, чтобы показать подробную информацию." << std::endl;
	std::cout << "apply [number] - подать заявку на участие в проекте";
}

Interface::~Interface()
{
	for (std::map<std::string, std::vector<std::string>>::iterator itr = commands.begin(); itr != commands.end(); itr++)
	{
		itr->second.clear();
	}
	commands.clear();
}