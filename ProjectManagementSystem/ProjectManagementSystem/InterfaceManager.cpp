#include "InterfaceManager.h"

#include "UserClass.h"
#include "ProjectClass.h"
#include "Database.h"
#include "NotificationStruct.h"

InterfaceManager::InterfaceManager()
{
	database = new Database();
	currentUser = NULL;
	status = "start";
	commands = {
		{"start", {"register [name] [password] - зарегистрироваться в системе", "login [name] [password] - войти в систему", "help - просмотр доступных команд", "exit - завершить выполнение программы"}},
		{"logged_in",{"create_project - создать проект", "my_projects - вывести список ваших текущих проектов", "edit_info - изменить информацию", "check_notifications - проверить уведомления", "logout - выйти из системы", "help - просмотр доступных команд"}}
	};
	database->createUser("Thomas", "12345", 7, "c++, sex, programming, turbo", "SEX, monster energy), realno flexim");
	database->createUser("GoldSwan", "pepega_cool", 6, "c++, programming, gaming, flex", "programming, flex, swag");
	database->createUser("admin", "admin", 99, "programming, c++, flex, administration", "flex, beer, cool");
	currentUser = database->getUser("Thomas");
	database->createProject(currentUser, "Test", "Testit", "mnogo testit", "testint", "putin", "11/11/1111", "c++, programming");
	database->getProject("Test")->addParticipant(currentUser);
	currentUser->addProject(database->getProject("Test"));
	database->getUser("Thomas")->addNewNotification(Notification(message, "test text owo", "admin", "Test"));
	database->createProject(database->getUser("GoldSwan"), "Gaming", "Testit", "mnogo testit", "testint", "putin", "11/11/1111", "turbo");
	database->getUser("Thomas")->addNewNotification(Notification(invitation, "hey bro here is a project to do!", "GoldSwan", "Gaming"));
	database->getUser("Thomas")->addNewNotification(Notification(notify, "hey bro I want to work on this project too!", "GoldSwan", "Test"));

}

void InterfaceManager::init() {

	welcome();
	do {
		fflush(stdin);
		std::cin >> input;
		std::cout << std::endl;
		if (input == "exit")
			break;

		else if (input == "register") {

			std::string name;
			std::string password;
			std::cin >> name;
			std::cin >> password;
			registerUser(name, password);
		}
			
		else if (input == "login") {

			std::string name;
			std::string password;
			std::cin >> name;
			std::cin >> password;
			login(name, password);
		}
			
		else if (input == "help")
			help();
		else
		{
			std::cout << "Введена некорректная команда. Попробуйте еще раз." << std::endl;
		}
	} while (true);
}

void InterfaceManager::welcome() { // Welocome message.


	std::cout << std::endl;
	std::cout << "Combo-Meal Software, Peter the Great St.Petersburg Polytechnic University" << std::endl;
	std::cout << "Используйте help для вывода доступных команд" << std::endl;

}

void InterfaceManager::registerUser(std::string name, std::string password) {

	if (database->checkUser(name)) {
		fflush(stdin);
		std::string prer;
		std::string studyFields;
		int free_time;
		std::cout << "Добро пожаловать, " << name << "!" << std::endl;
		std::cout << "Введите дополнительные данные. В дальнейшем информация может быть изменена." << std::endl;
		std::cout << "Выйти - back" << std::endl;
		std::cout << "Введите Ваши навыки через запятую: " << std::endl;
		std::getline(std::cin, prer);
		std::getline(std::cin, prer);
		if (prer == "back")
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
		database->createUser(name, password, free_time, prer, studyFields);
		std::cout << std::endl;
		std::cout << "Успешно создан новый профиль \"" << name << "\"!" << std::endl;
		std::cout << "Пожалуйста, зайдите в систему под своим именем и паролем" << std::endl;
	}
	else
		std::cout << "Пользователь с таким именем уже существует." << std::endl;
	
}

void InterfaceManager::login(std::string name, std::string password) {

	//User* user = database->getUser(name);
	if (database->getUser(name)->checkPassword(password)) {

		currentUser = database->getUser(name);
		status = "logged_in";
		fflush(stdin);
		std::getline(std::cin, input);
		std::cout << "Добро пожаловать, " << name << "!" << std::endl;
		std::cout << "Новых уведомлений: " << currentUser->checkNotifications() << std::endl;
		do {

			std::cout << "Для просмотра доступных команд используйте help." << std::endl;
			std::cout << "Для выхода из системы используйте logout." << std::endl;
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
			{
				if (currentUser->checkNotifications() == 0)
				{
					std::cout << "У вас нет новых уведомлений." << std::endl;
				}
				else
					checkNotifications();
			}
			
			else
				std::cout << "Введена некорректная команда. Попробуйте еще раз. Введите help для просмотра всех команд." << std::endl;

		} while (true);
		
	}
	else {

		std::cout << " Введено неверное имя или пароль. Попробуйте еще раз." << std::endl;

	}
}

void InterfaceManager::logout() {

	currentUser = NULL;
	status = "start";
	welcome();

}

void InterfaceManager::help() {

	for (int i = 0; i < commands[status].size(); i++) {

		std::cout << commands[status][i] << std::endl;

	}
	std::cout << std::endl;

}

void InterfaceManager::editInfo() {

	while (true) {

		std::cout << *currentUser << std::endl;
		std::cout << std::endl;
		std::cout << "Какую информацию вы бы хотели изменить?" << std::endl;
		std::cout << "введите одно из следующих: password, time, skills, interests" << std::endl;
		std::cout << "Выйти - back" << std::endl;
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
		else if (input == "password") {

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
					std::cout << std::endl;
					break;
				currentUser->changeInfo(2, input);
				std::cout << "Пароль успешно изменен." << std::endl;
			}
			else {

				std::cout << "Введен неверный текущий пароль. Попробуйте еще раз." << std::endl;

			}
			
		}
		else if (input == "time") {

			fflush(stdin);
			std::cout << "Введите число, на которое нужно увеличить Ваше текущее свободное время. " << std::endl;
			std::cout << "(если время нужно уменьшить, то введите отрицательное число)" << std::endl;
			std::getline(std::cin, input);
			std::cout << std::endl;
			currentUser->changeInfo(3, input);
			std::cout << "Время успешно изменено." << std::endl;

		}
		else if (input == "skills") {

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
		else if (input == "interests") {

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
		else
		{
			std::cout << "Введена некорректная команда. Попробуйте еще раз." << std::endl;
		}

	}
	
}

void InterfaceManager::displayNotification(Notification notification) {

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

void InterfaceManager::checkNotifications() {

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
					std::cout << "Введите delete для удаления уведомления или leave, чтобы вернуться";
					fflush(stdin);
					std::getline(std::cin, input);
					if (input == "delete"){
			
						notifications.erase(notifications.begin() + number);
						break;
			
					}
					else
						break;
			
				case invitation:
					std::cout << "Введите accept для записи в проект, decline чтобы удалить уведомление или \"Оставить\", чтобы вернуться";
					fflush(stdin);
					std::getline(std::cin, input);
					if (input == "accept") {
						
						database->getProject(notifications[number].project)->addParticipant(currentUser);
						currentUser->addProject(database->getProject(notifications[number].project));
						notifications.erase(notifications.begin() + number);
						break;
			
					}
					else if (input == "decline"){
			
						notifications.erase(notifications.begin() + number);
						break;
			
					}
					else
						break;
			
				case rating:
					std::cout << "Хотите ли принять участие в оценке участников проекта?" << std::endl;
					std::cout << "Введите yes, чтобы продолжить, no чтобы удалить уведомление или leave, чтобы вернуться" << std::endl;
					fflush(stdin);
					std::getline(std::cin, input);
					if (input == "yes") {

						Project* project = database->getProject(notifications[number].project);
						std::map<std::string, User*> participants = project->getParticipants();
						for (const std::pair<std::string, User*>& p : participants) {

							if (p.second == currentUser) {

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

						}
						participants.clear();
					}
					else if (input == "no") {
			
						notifications.erase(notifications.begin() + number);
						break;
			
					}
					else
						break;

				case notify:

					std::cout << "Введите accept для записи в проект, decline чтобы удалить уведомление и послать отказ или leave, чтобы вернуться";
					fflush(stdin);
					std::getline(std::cin, input);
					if (input == "accept") {
						
						std::cout << "Напишите текст сообщения о принятии (или оставьте пустым):" << std::endl;
						fflush(stdin);
						std::getline(std::cin, input);
						if (input == "back")
							break;
						std::cout << std::endl;
						Notification tempn = Notification(message, "Вы приняты: " + input, currentUser->getName(), notifications[number].project);
						database->getUser(notifications[number].sender)->addNewNotification(tempn);
						database->getProject(notifications[number].project)->addParticipant(database->getUser(notifications[number].sender));
						database->getUser(notifications[number].sender)->addProject(database->getProject(notifications[number].project));
						notifications.erase(notifications.begin() + number);
						break;

					}
					else if (input == "decline") {
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

void InterfaceManager::createProject()
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
	if (!database->checkProject(name))
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
	database->getProject(name)->addParticipant(currentUser);
	currentUser->addProject(database->getProject(name));
	return;
}

void InterfaceManager::findProjects()
{
	fflush(stdin);
	std::cout << "Выйти - back";
	std::vector<Project*> *temp = &(database->findProjects(currentUser->getPrerequisites()));
	std::map<std::string, Project*>* tempcu = &(currentUser->getCurrentProjects());
	for (int i = 0; i < temp->size(); i++)
	{
		if (tempcu->count(temp->operator[](i)->getName()) == 1)
			temp->erase(temp->begin() + i);
	}
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
				std::cout << *(temp->operator[](std::stoi(input)));
			}
	}
	for (int i = 0; i < temp->size(); i++)
	{
		delete temp->operator[](i);
	}
	return;
}

void InterfaceManager::findParticipants(std::string name)
{
	fflush(stdin);
	Project* tempPro = database->getProject(name);
	std::cout << "Выйти - back";
	std::vector<User*> temp = database->findParticipants(tempPro->getPrerequisites());
	std::map<std::string, User*> tempPar = tempPro->getParticipants();
	bool flag = false;
	while (flag == false)
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if (tempPar.count(temp[i]->getName()) == 1)
			{
				temp.erase(temp.begin() + i);
				break;
			}
			if (i == (temp.size() - 1))
				flag = true;
		}
	}
	std::cout << "Подходящие вам пользователи:" << std::endl;
	if (temp.size() == 0)
	{
		std::cout << "Подходящие пользователи отсутсвуют." << std::endl;
		return;
	}
	for (int i = 0; i < temp.size(); i++)
	{
		std::cout << i << " " << temp[i]->getName() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Введите номер пользователя, чтобы показать подробную информацию." << std::endl;
	std::cout << "invite [number] - отправить приглашение в проект" << std::endl;
	while (true)
	{
		std::cin >> input;
		if (input == "invite")
		{
			std::cin >> input;
			fflush(stdin);
			std::string message;
			std::cout << "Введите ваше сообщение." << std::endl;
			std::getline(std::cin, message);
			Notification tempn = Notification(invitation, message, currentUser->getName(), name);
			temp[std::stoi(input)]->addNewNotification(tempn);
			std::cout << "Приглашение отправлено!" << std::endl;
		}
		else
			if (input == "back")
				break;
			else
			{
				std::cout << *(temp[std::stoi(input)]);
			}
	}
	temp.clear();
	return;
}

void InterfaceManager::displayProjects()
{
	std::string name;
	std::cout << "Выйти - back" << std::endl;
	std::map<std::string, Project*> projects = currentUser->getCurrentProjects();
	std::cout << "Вы состоите в следующих проектах: " << std::endl;
	if (projects.size() == 0)
	{
		std::cout << "Вы не состоите ни в одном проекте." << std::endl;
		return;
	}
	for (const std::pair<std::string, Project*> p : projects)
	{
		std::cout << p.first << " " << p.second->getObjective() << std::endl;
	}
	std::cout << "Введите номер проекта, чтобы показать подробную информацию." << std::endl;
	std::cout << "edit [name] - изменить информацию о проекте (только для инициаторов и менеджеров проекта)" << std::endl;
	std::cout << "find_participants [name] - найти участников для проекта" << std::endl;
	while (true)
	{
		std::cin >> input;
		if (input == "edit")
		{
			std::cin >> name;
			fflush(stdin);
			if (currentUser->getName() == projects[name]->getInitiator()->getName() || currentUser->getName() == projects[name]->getManager()->getName())
				editProject(name);
			else
				std::cout << "Вы не обладаете достаточными правами." << std::endl;
		}
		else
			if (input == "find_participants")
			{
				std::cin >> name;
				findParticipants(name);
				std::cout << "Поиск участников завершен" << std::endl;
			}
			else
				if (input == "back")
					break;
				else
				{
					std::cout << *(projects[name]);
				}
	}
	projects.clear();
	return;
}

void InterfaceManager::editProject(std::string name)
{
	Project* project = database->getProject(name);
	while (true)
	{
		std::cout << "Какую информацию вы бы хотели изменить?: Статус, Цель, Задачи, Предметная область, Заказчик, Дедлайн, Необходимые навыки, Менеджер (только для инициаторов)" << std::endl;
		std::cout << "Закрыть проект - close (только для инициаторов)" << std::endl;
		std::cout << "Выйти - back" << std::endl;
		fflush(stdin);
		std::getline(std::cin, input);
		if (input == "back")
			break;
		else
		{
			if (input == "Статус")
			{
				std::cout << "Введите статус (Initialization, Recruitment, Active, Closed)" << std::endl;
				std::getline(std::cin, input);
				if ((input != "Initialization") && (input != "Recruitment") && (input != "Active") && (input != "Closed"))
					std::cout << "Введен неверный статус";
				else
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
												database->getUser(input)->addProject(project);
											}
											else
												std::cout << "У вас недостаточно прав." << std::endl;
										}
										else
											if (input == "close")
											{
												if (project->getInitiator()->getName() == currentUser->getName())
												{
													while (true)
													{
														std::cout << "Закрыть проект " << name << " ? Y/N" << std::endl;
														std::cin >> input;
														if (input == "Y" || input == "N")
															break;
													}
													if (input == "Y")
													{
														std::string mes;
														std::map<std::string, User*> temp = project->getParticipants();
														temp.insert({ project->getManager()->getName(), project->getManager() });
														std::cout << "Участники проекта получат уведомления с просьбой оценить работу других участников. Введите ваше прощальное сообщение." << std::endl;
														std::getline(std::cin, mes);
														Notification tempNot = Notification(rating, mes, currentUser->getName(), name);
														for (const std::pair<std::string, User*>& p : temp)
														{
															p.second->addNewNotification(tempNot);
														}
														std::cout << "Проект был успешно закрыт." << std::endl;
													}
													std::cout << "Вы избежали непоправимой ошибки." << std::endl;
												}
												else
													std::cout << "У вас недостаточно прав." << std::endl;
											}
		}
	}
	delete project;
	return;
}

InterfaceManager::~InterfaceManager()
{

}