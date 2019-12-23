#include "UserClass.h"
#include "ProjectClass.h"
#include "UserInfoManager.h"
#include "RatingManager.h"
#include "NotificationManager.h"
#include "NotificationStruct.h"

User::User(std::string n, std::string pass, int free_time, std::string prerequisites, std::string StudyFields) {

	notifications = new NotificationManager();
	ratingManager = new RatingManager();
	infoManager = new UserInfoManager();
	infoManager->setName(n);
	infoManager->changeFreetime(free_time);
	infoManager->addPrerequisites(prerequisites);
	infoManager->addStudyFields(StudyFields);
	
}
void User::changeInfo(int i, std::string input) {

	switch (i)
	{
	case 1:
		infoManager->setName(input);
		break;

	case 2:
		infoManager->changePassword(input);
		break;

	case 3:
		int free_time = stoi(input);
		infoManager->changeFreetime(free_time);
		break;
	
	case 4:
		infoManager->addPrerequisites(input);
		break;

	case 5:
		infoManager->addStudyFields(input);
		break;

	default:
		break;
	}

}

std::string User::getName() {

	infoManager->getName();

}

int User::getFreetime() {

	infoManager->getFreetime();
  
}

float User::getRating() {

	ratingManager->getRating();

}

std::map<std::string, Project*> User::getCurrentProjects() {

	infoManager->getCurrentProjects();

}

std::map<std::string, Project*> User::getFinishedProjects() {

	infoManager->getFinishedProjects();

}

std::vector<std::string> User::getPrerequisites() {

	infoManager->getPrerequisites();

}

std::vector<std::string> User::getStudyFields() {

	infoManager->getStudyFields();

}

bool User::checkPassword(std::string pass) {

	infoManager->checkPassword(pass);

}

void User::collectRating(float newRating) {

	ratingManager->collectRating(newRating);

}

void User::deleteProject(std::string name) {

	infoManager->deleteProject(name);
  
}

std::vector<Notification> User::extractNotifications() {

	return notifications->getNewNots();

}
void User::returnNotifications(std::vector<Notification> returned) {

	notifications->updateNotifications(returned);

}

int User::checkNotifications() {

	return notifications->checkNotifications();

}

void User::addNewNotification(Notification notification) {

	notifications->addNotification(notification);

}

User::~User() {

	std::map<std::string, Project*> temp = infoManager->getCurrentProjects();
	for (const std::pair<std::string, Project*>& p : temp) {

		p.second->removeParticipant(infoManager->getName());

	}
	temp = infoManager->getFinishedProjects();
	for (const std::pair<std::string, Project*>& p : temp) {

		p.second->removeParticipant(infoManager->getName());

	}
	delete notifications;
	delete infoManager;
	delete ratingManager;

}

std::ostream& operator<<(std::ostream& os, const User& user) {

	os << "������������ " << user.infoManager->getName() << std::endl;
	os << "�������: " << user.ratingManager->getRating() << std::endl;
	os << "������� �������: " << user.infoManager->getCurrentProjects().size() << std::endl;
	os << "����������� �������: " << user.infoManager->getFinishedProjects().size() << std::endl;
	os << "������: ";
	std::vector<std::string> temp = user.infoManager->getPrerequisites();
	for (int i = 0; i < temp.size() - 1; i++) {
		os << temp[i];
		os << ", ";
	}
	os << temp[temp.size()-1];
	os << std::endl;
	os << "�������������� ���������� �������: ";
	temp = user.infoManager->getStudyFields();
	for (int i = 0; i < temp.size() - 1; i++) {
		os << temp[i];
		os << ", ";
	}
	os << temp[temp.size()];
	os << std::endl;
	os << "Free time: " << user.infoManager->getFreetime() << std::endl;

}