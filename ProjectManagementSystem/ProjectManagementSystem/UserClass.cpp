#include "UserClass.h"

User::User(std::string n, std::string pass, int free_time, std::string prerequisites, std::string StudyFields) {

	setName(n);
	freetime = 0;
	changeFreetime(free_time);
	addPrerequisites(prerequisites);
	addStudyFields(StudyFields);

}
void User::setName(std::string n) {

	name = n;

}
void User::changeFreetime(int time); {

	freetime += time; // can be +time or -time, depends on what we want. but we need to check that freetime is not below zero! #exception

}
void User::addPrerequisites(std::string pr) { // checking right input? #exception

	while (pr.find(",") != std::string::npos)
	{
		Prerequisites.push_back(pr.substr(0, pr.find(",")));
		pr.substr(pr.find(",") + 1);
	}
	Prerequisites.push_back(pr);

}
void User::addStudyFields(std::string sf) { // checking right input? #exception

	while (sf.find(",") != std::string::npos)
	{
		StudyFields.push_back(sf.substr(0, sf.find(",")));
		sf.substr(sf.find(",") + 1);
	}
	StudyFields.push_back(sf);

}
void User::addCurrentProjects(Project& project) {

	/*

	 currentProjects.insert(std::make_pair(project.getName(), project));

	 code below is more safe IMO, we don't need to check is project already in currentProjects or not
	 if it is already inside currentProjects, nothing happens

	 */

	currentProjects[project.getName()] = project;

}
void User::addFinishedProjects(Project& project) { // can be a situation that project is added to finishedProjects, but it was not in currentProjects? #exception ?

	finishedProjects[project.getName()] = project;
	std::map<std::string, Project*> ::iterator old_project;
	old_project = currentProjects.find(project.getName());
	currentProjects.erase(old_project);

}
std::string User::getName() {

	return name;

}
int User::getFreetime() {

	return freetime;

}
float User::getRating() {

	float count;
	int sum = 0;
	//rating.size()
	for (int i = 0; i < rating.size(); i++)
		sum += rating[i];
	count = (float)sum / rating.size();
	return count;

}
std::map<std::string, Project*> User::getCurrentProjects() {

	return currentProjects();

}
std::map<std::string, Project*> User::getFinishedProjects() {

	return finishedProjects();

}
std::vector<std::string> User::getPrerequisites() {

	return prerequisites;

}
bool User::checkPassword(std::string pass) {

	if (pass == password)
		return true;
	else
		return false;

}
void User::collectRating(float newRating) {

	rating.push_back(newRating);

	~
}
User::~User() {

	// Gotta work on this

}