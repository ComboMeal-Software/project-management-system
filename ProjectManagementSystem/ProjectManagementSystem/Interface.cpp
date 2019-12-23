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
		{"start", {"register [name] [password] - зарегистрироваться в системе", "login [name] [password] - войти в систему"}},
		{"logged_in",{"create_project - создать проект", "my_projects - вывести список ваших текущих проектов", "edit_info - изменить информацию", "check_notifications - проверить уведомления"}}
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
	fflush(stdin);
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
			fflush(stdin);
			std::string message;
			std::cout << "Введите ваше сообщение." << std::endl;
			std::getline(std::cin, message);
			Notification tempn = Notification(notify, message, currentUser->getName(), temp->operator[](std::stoi(input))->getName());
			temp->operator[](std::stoi(input))->getInitiator()->addNewNotification(tempn);
		}
		else
			if (input == "back")
				break;
			else
			{
				std::cout << temp->operator[](std::stoi(input));
			}
	}
	for (int i = 0; i < temp->size(); i++)
	{
		delete temp->operator[](i);
	}
	delete[] temp;
	return;
}

void Interface::displayProjects()
{
	std::string name;
	std::cout << "Выйти - back";
	std::map<std::string, Project*>* temp = &(currentUser->getCurrentProjects());
	std::cout << "Вы состоите в следующих проектах: " << std::endl;
	if (temp->size() == 0)
	{
		std::cout << "Вы не состоите ни в одном проекте." << std::endl;
		return;
	}
	for (const std::pair<std::string, Project*>& p : temp->begin)
	{
		std::cout << p.first << " " << p.second->getName();
	}
	std::cout << "Введите номер проекта, чтобы показать подробную информацию." << std::endl;
	std::cout << "edit [name] - изменить информацию о проекте (только для инициаторов и менеджеров проекта)";
	while (true)
	{
		std::cin >> input;
		if (input == "edit")
		{
			std::cin >> name;
			fflush(stdin);
			if (currentUser->getName() == temp->operator[](name)->getInitiator()->getName() || currentUser->getName() == temp->operator[](name)->getManager()->getName())
				editProject(name);
			else
				std::cout << "Вы не обладаете достаточными правами." << std::endl;
		}
		else
			if (input == "back")
				break;
			else
			{
				std::cout << temp->operator[](name);
			}
	}
	for (std::map<std::string, Project*>::iterator itr = temp->begin(); itr != temp->end(); itr++)
	{
		delete (itr->second);
	}
	temp->clear();
	return;
}

void Interface::editProject(std::string name)
{
	Project* project = database->getProject(name);
	while (true)
	{
		std::cout << "Какую информацию вы бы хотели изменить?: Статус, Цель, Задачи, Предметная область, Заказчик, Дедлайн, Необходимые навыки, Менеджер (только для инициаторов)" << std::endl;
		std::cout << "Выйти - back";
		fflush(stdin);
		std::getline(std::cin, input);
		if (input == "back")
			break;
		else
		{
			if (input == "Статус")
			{
				std::cout << "Введите статус ";
				std::getline(std::cin, input);
				project->setStatus(input);
			}
			else
				if (input == "Цель")
				{
					std::cout << "Введите цель ";
					std::getline(std::cin, input);
					project->setObjective(input);
				}
				else
					if (input == "Задачи")
					{
						std::cout << "Введите задачи ";
						std::getline(std::cin, input);
						project->setTasks(input);
					}
					else
						if (input == "Предметная область ")
						{
							std::cout << "Введите предметную область ";
							std::getline(std::cin, input);
							project->setSubjectField(input);
						}
						else
							if (input == "Заказчик")
							{
								std::cout << "Введите заказчика ";
								std::getline(std::cin, input);
								project->setClient(input);
							}
							else
								if (input == "Дедлайн")
								{
									std::cout << "Введите дедлайн (дд/мм/гггг) ";
									std::getline(std::cin, input);
									project->setDeadline(input);
								}
								else
									if (input == "Необходимые навыки")
									{
										std::cout << "Введите необходимые навыки";
										std::getline(std::cin, input);
										project->setPrerequisites(input);
									}
									else
										if (input == "Менеджер")
										{
											if (project->getInitiator()->getName() == currentUser->getName())
											{
												std::cout << "Введите имя менеджера";
												std::getline(std::cin, input);
												project->setManager(database->getUser(input));
											}
											else
												std::cout << "У вас недостаточно прав.";
										}
		}
	}
	delete project;
	return;
}

Interface::~Interface()
{
	for (std::map<std::string, std::vector<std::string>>::iterator itr = commands.begin(); itr != commands.end(); itr++)
	{
		itr->second.clear();
	}
	commands.clear();
}