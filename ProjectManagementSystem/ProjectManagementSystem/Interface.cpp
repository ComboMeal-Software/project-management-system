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
		{"start", {"register [name] [password] - зарегистрироваться в системе", "login [name] [password] - войти в систему", "help - просмотр доступных команд", "exit - завершить выполнение программы"}},
		{"logged_in",{"create_project - создать проект", "my_projects - вывести список ваших текущих проектов", "edit_info - изменить информацию", "check_notifications - проверить уведомления", "logout - выйти из системы", " help - просмотр доступных команд"}}
	};
}

void Interface::init() {

	welcome();
	do {
		fflush(stdin);
		std::getline(std::cin, input);
		std::cout << std::endl;
		if (input == "exit")
			break;

		if (input == "register") {

			std::string name;
			std::string password;
			std::getline(std::cin, name);
			std::getline(std::cin, password);
			registerUser(name, password);
		}
			
		if (input == "login") {

			std::string name;
			std::string password;
			std::getline(std::cin, name);
			std::getline(std::cin, password);
			login(name, password);

		}
			
		if (input == "help")
			help();

	} while (true);
	
	return;
}

void Interface::welcome() { // Welocome message.


	std::cout << std::endl;
	std::cout << "Combo-Meal Software, Peter the Great St.Petersburg Polytechnic University" << std::endl;
	std::cout << "Используйте help для вывода доступных команд" << std::endl;

}

void Interface::registerUser(std::string name, std::string password) {

	if (database->checkUser(name)) {
		fflush(stdin);
		std::string prerequisites;
		std::string studyFields;
		int free_time;
		std::cout << "Добро пожаловать, " << name << "!" << std::endl;
		std::cout << "Введите дополнительные данные. В дальнейшем информация может быть изменена." << std::endl;
		std::cout << "Выйти - back" << std::endl;
		std::cout << "Введите Ваши навыки через запятую: ";
		std::getline(std::cin, prerequisites);
		if (prerequisites == "back")
			return;
		std::cout << std::endl;
		fflush(stdin);
		std::cout << "Введите Ваши предпочитаемые предметные области через запятую: ";
		std::getline(std::cin, studyFields);
		if (studyFields == "back")
			return;
		std::cout << std::endl;
		fflush(stdin);
		std::cout << "Введите количество Вашего свободное время, которое вы готовы уделять проектам каждую неделю: ";
		std::string time_string;
		std::getline(std::cin, time_string);
		if (time_string == "back")
			return;
		free_time = std::stoi(time_string); // #exception
		fflush(stdin);
		database->createUser(name, password, free_time, prerequisites, studyFields);
		std::cout << std::endl;
		std::cout << "Успешно создан новый профиль \"" << name << "\"!" << std::endl;
		std::cout << "Пожалуйста, зайдите в систему под своим именем и паролем" << std::endl;
	}
	else
		std::cout << "Пользователь с таким именем уже существует." << std::endl;
	
}

void Interface::login(std::string name, std::string password) {

	User* user = database->getUser(name);
	if (user->checkPassword(password)) {

		currentUser = user;
		delete user;
		status = "logged_in";
		std::cout << "Добро пожаловать, " << name << "!" << std::endl;
		std::cout << "Новых уведомлений: " << user->checkNotifications() <<std::endl;
		std::cout << "Для просмотра доступных команд используйте help." << std::endl;
		std::cout << "Для выхода из системы используйте logout." << std::endl;
		do {

			fflush(stdin);
			std::getline(std::cin, input);
			std::cout << std::endl;
			if (input == "logout") {

				logout();
				break;

			}

			else if (input == "help")
				help();

			else if (input == "create_project")
				createProject();

			else if (input == "my_projects")
				displayProjects();

			else if (input == "edit_info")
				editInfo();

			else if (input == "check_notifications")
				checkNotifications();

			else
				std::cout << "Введена некорректная команда. Попробуйте еще раз. Введите help для просмотра всех команд.";

		} while (true);
		
	}
	else {

		std::cout << " Введено неверное имя или пароль. Попробуйте еще раз." << std::endl;

	}
}

void Interface::logout() {

	currentUser = NULL;
	status = "start";
	welcome();

}

void Interface::help() {

	for (int i = 0; i < commands[status].size(); i++) {

		std::cout << commands[status][i] << std::endl;

	}
	std::cout << std::endl;

}

void Interface::editInfo() {

	while (true) {

		std::cout << currentUser << std::endl;
		std::cout << std::endl;
		std::cout << "Какую информацию вы бы хотели изменить?" << std::endl;
		std::cout << "введите одно из следующих: Пароль, Время, Навыки, Предметные области" << std::endl;
		std::cout << "Выйти - back";
		fflush(stdin);
		std::getline(std::cin, input);
		if (input == "back")
			break;
		/*else if (input == "Имя"){  ВНИМАНИЕ! ИЗМЕНЕНИЕ ИМЕНИ НЕ ВЛИЯЕТ НА DATABASE!

			fflush(stdin);
			std::cout << "Введите имя: ";
			std::getline(std::cin, input);
			std::cout << std::endl;
			if (input == "back")
				break;
			currentUser->changeInfo(1, input);
			std::cout << "Имя успешно изменено." << std::endl;

		}*/
		else if (input == "Пароль") {

			fflush(stdin);
			std::cout << "Введите текущий пароль: ";
			std::getline(std::cin, input);
			std::cout << std::endl;
			if (input == "back")
				break;
			if (currentUser->checkPassword(input)) {

				fflush(stdin);
				std::cout << "Введите новый пароль: ";
				std::getline(std::cin, input);
				std::cout << std::endl;
				if (input == "back")
					break;
				currentUser->changeInfo(2, input);
				std::cout << "Пароль успешно изменен." << std::endl;
			}
			else {

				std::cout << "Введен неверный текущий пароль. Попробуйте еще раз." << std::endl;

			}
			
		}
		else if (input == "Время") {

			fflush(stdin);
			std::cout << "Введите число, на которое нужно увеличить Ваше текущее свободное время. " << std::endl;
			std::cout << "(если время нужно уменьшить, то введите отрицательное число)" << std::endl;
			std::getline(std::cin, input);
			std::cout << std::endl;
			currentUser->changeInfo(3, input);
			std::cout << "Время успешно изменено." << std::endl;

		}
		else if (input == "Навыки") {

			fflush(stdin);
			std::cout << "Внимание! Список Ваших навыков будет удален, чтобы вы ввели новые. " << std::endl;
			std::cout << "Чтобы продолжить, нажмите Enter. Чтобы вернуться, введите back." << std::endl;
			std::getline(std::cin, input);
			std::cout << std::endl;
			if (input == "back")
				break;
			else {
				std::cout << "Введите Ваши навыки через запятую: ";
				fflush(stdin);
				std::getline(std::cin, input);
				if (input == "back")
					break;
				std::cout << std::endl;
				currentUser->changeInfo(4, input);
				std::cout << "Навыки успешно изменены." << std::endl;
			}
		}
		else if (input == "Предметные области") {

			fflush(stdin);
			std::cout << "Внимание! Список Ваших предметных областей будет удален, чтобы вы ввели новые. " << std::endl;
			std::cout << "Чтобы продолжить, нажмите Enter. Чтобы вернуться, введите back." << std::endl;
			std::getline(std::cin, input);
			std::cout << std::endl;
			if (input == "back")
				break;
			else {
				std::cout << "Введите Ваши предметные области через запятую: ";
				fflush(stdin);
				std::getline(std::cin, input);
				if (input == "back")
					break;
				std::cout << std::endl;
				currentUser->changeInfo(5, input);
				std::cout << "Навыки успешно изменены." << std::endl;
			}

		}

	}
	
}

void Interface::displayNotification(Notification notification) {

	std::cout << " Тип: ";
	switch (notification.type)
	{
	case message:
		std::cout << "Сообщение";
		break;
	case invitation:
		std::cout << "Приглашение";
		break;
	case rating:
		std::cout << "Оценка";
		break;
	case notify:
		std::cout << "Запрос";
		break;
	default:
		break;
	}
	std::cout << ",  Отправитель: " << notification.sender;
	std::cout << ",  Проект: " << notification.project;
	std::cout << std::endl;

}

void Interface::checkNotifications() {

	std::vector<Notification> notifications = currentUser->extractNotifications();
	while (true) {

		std::cout << "Новые уведомления:" << std::endl;
		for (int i = 0; i < notifications.size(); i++) {

			std::cout << i + 1 << ")";
			displayNotification(notifications[i]);

		}
		std::cout << std::endl;
		std::cout << "Введите номер уведомления чтобы показать подробности" << std::endl;
		std::cout << "Выйти - back" << std::endl;
		fflush(stdin);
		std::getline(std::cin, input);
		if (input == "back")
			break;
		std::cout << std::endl;
		int number = stoi(input) - 1;
		displayNotification(notifications[number]);
		std::cout << "Текст:" << std::endl;
		std::cout << notifications[number].text << std::endl;
		switch (notifications[number].type)
				{
				case message:
					std::cout << "Введите \"Удалить\" для удаления уведомления или \"Оставить\", чтобы вернуться";
					if (input == "Удалить"){
			
						notifications.erase(notifications.begin() + number);
						break;
			
					}
					else
						break;
			
				case invitation:
					std::cout << "Введите \"Принять\" для записи в проект, \"Отказаться\" чтобы удалить уведомление или \"Оставить\", чтобы вернуться";
					if (input == "Принять") {
						
						database->getProject(notifications[number].project)->addParticipant(currentUser);
						notifications.erase(notifications.begin() + number);
						break;
			
					}
					else if (input == "Отказаться"){
			
						notifications.erase(notifications.begin() + number);
						break;
			
					}
					else
						break;
			
				case rating:
					std::cout << "Хотите ли принять участие в оценке участников проекта?" << std::endl;
					std::cout << "Введите \"Да\", чтобы продолжить, \"Нет\" чтобы удалить уведомление или \"Оставить\", чтобы вернуться" << std::endl;
					if (input == "Да") {

						Project* project = database->getProject(notifications[number].project);
						std::map<std::string, User*> participants = project->getParticipants();
						for (const std::pair<std::string, User*>& p : participants) {

							if (p.second == currentUser) {

								delete p.second;
								continue;

							}
							else {

								std::cout << "Какую оценку Вы хотите дать участнику " << p.first << "?" << std::endl;
								std::cout << "Введите оценку от 1 до 10: ";
								do {
									fflush(stdin);
									std::getline(std::cin, input);
									std::cout << std::endl;
									int rate = stoi(input); // #exception
									if (rate > 10 || rate < 1) {
										std::cout << "Введена неправильная оценка, попробуйте еще раз: ";
									}
									else {

										break;

									}
								} while (true);
								
							}
							delete p.second;

						}
						delete project;

					}
					else if (input == "Нет") {
			
						notifications.erase(notifications.begin() + number);
						break;
			
					}
					else
						break;

				case notify:

					std::cout << "Введите \"Принять\" для записи в проект, \"Отказать\" чтобы удалить уведомление и послать отказ или \"Оставить\", чтобы вернуться";
					if (input == "Принять") {
						
						std::cout << "Напишите текст сообщения о принятии (или оставьте пустым):" << std::endl;
						fflush(stdin);
						std::getline(std::cin, input);
						if (input == "back")
							break;
						std::cout << std::endl;
						Notification tempn = Notification(message, "Вы приняты: " + input, currentUser->getName(), notifications[number].project);
						database->getUser(notifications[number].sender)->addNewNotification(tempn);
						database->getProject(notifications[number].project)->addParticipant(database->getUser(notifications[number].sender));
						notifications.erase(notifications.begin() + number);
						break;

					}
					else if (input == "Отказать") {
						std::cout << "Напишите текст отказа (или оставьте пустым):" << std::endl;
						fflush(stdin);
						std::getline(std::cin, input);
						if (input == "back")
							break;
						std::cout << std::endl;
						Notification tempn = Notification(message, "Отказ: " + input, currentUser->getName(), notifications[number].project);
						database->getUser(notifications[number].sender)->addNewNotification(tempn);
						notifications.erase(notifications.begin() + number);
						break;

					}
					else
						break;
			
				default:
			
					break;
				}
	}
	currentUser->returnNotifications(notifications);
	
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