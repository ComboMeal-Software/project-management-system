#include "UserClass.h"
#include "ProjectClass.h"
#include "UserInfoManager.h"
#include "RatingManager.h"

User::User(std::string n, std::string pass, int free_time, std::string prerequisites, std::string StudyFields) {

	notifications = new NotificationManager();
	ratingManager = new RatingManager();
	infoManager = new UserInfoManager();
	infoManager->setName(n);
	infoManager->changeFreetime(free_time);
	infoManager->addPrerequisites(prerequisites);
	infoManager->addStudyFields(StudyFields);
	
}
void User::changeInfo() {

	// Gotta work on this

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
User::~User() {

	for (const std::pair<std::string, Project*>& p : infoManager->getCurrentProjects()) {

		p.second->removeParticipant(infoManager->getName());

	}
	for (const std::pair<std::string, Project*>& p : infoManager->getFinishedProjects()) {

		p.second->removeParticipant(infoManager->getName());

	}
	delete notifications;
	delete infoManager;
	//delete ratingManager

}

std::ostream& operator<<(std::ostream& os, const User& user) {

	os << "User " << user.infoManager->getName() << std::endl;
	os << "Rating: " << user.ratingManager->getRating() << std::endl;
	os << "Current projects: " << user.infoManager->getCurrentProjects().size() << std::endl;
	os << "Finished projects: " << user.infoManager->getFinishedProjects().size() << std::endl;
	os << "Prerequisites: ";
	for (int i = 0; i < user.infoManager->getPrerequisites().size(); i++) {
		os << user.infoManager->getPrerequisites()[i];
		if (i != user.infoManager->getPrerequisites().size() - 1)
			os << ", ";
	}
	os << std::endl;
	os << "Study Fields: ";
	for (int i = 0; i < user.infoManager->getStudyFields().size(); i++) {
		os << user.infoManager->getStudyFields()[i];
		if (i != user.infoManager->getStudyFields().size() - 1)
			os << ", ";
	}
	os << std::endl;
	os << "Free time: " << user.infoManager->getFreetime() << std::endl;

}