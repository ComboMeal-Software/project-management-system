#include "UserInfoManager.h"
#include "UserClass.h"
#include "ProjectClass.h"

UserInfoManager::UserInfoManager() {

	freetime = 0;

}
void UserInfoManager::setName(std::string n) {

	name = n;

}
void UserInfoManager::changeFreetime(int time) {

	freetime += time; // can be +time or -time, depends on what we want. but we need to check that freetime is not below zero! #exception

}
void UserInfoManager::addPrerequisites(std::string pr) { // checking right input? #exception

	while (pr.find(",") != std::string::npos)
	{
		prerequisites.push_back(pr.substr(0, pr.find(",")));
		pr.substr(pr.find(",") + 1);
	}
	prerequisites.push_back(pr);

}
void UserInfoManager::addStudyFields(std::string sf) { // checking right input? #exception

	while (sf.find(",") != std::string::npos)
	{
		StudyFields.push_back(sf.substr(0, sf.find(",")));
		sf.substr(sf.find(",") + 1);
	}
	StudyFields.push_back(sf);

}
void UserInfoManager::addCurrentProjects(Project& project) {

	/*

	 currentProjects.insert(std::make_pair(project.getName(), project));

	 code below is more safe IMO, we don't need to check is project already in currentProjects or not
	 if it is already inside currentProjects, nothing happens

	 */

	currentProjects[project.getName()] = &project;

}
void UserInfoManager::addFinishedProjects(Project& project) { // can be a situation that project is added to finishedProjects, but it was not in currentProjects? #exception ?

	finishedProjects[project.getName()] = &project;
	/*std::map<std::string, Project*> ::iterator old_project;
	old_project = currentProjects.find(project.getName());
	currentProjects.erase(old_project);*/
	currentProjects.erase(project.getName());

}
std::string UserInfoManager::getName() {

	return name;

}
int UserInfoManager::getFreetime() {

	return freetime;

}
std::map<std::string, Project*> UserInfoManager::getCurrentProjects() {

	return currentProjects;

}
std::map<std::string, Project*> UserInfoManager::getFinishedProjects() {

	return finishedProjects;

}
std::vector<std::string> UserInfoManager::getPrerequisites() {

	return prerequisites;

}
std::vector<std::string> UserInfoManager::getStudyFields() {

	return StudyFields;

}
bool UserInfoManager::checkPassword(std::string pass) {

	if (pass == password)
		return true;
	else
		return false;

}
void UserInfoManager::deleteProject(std::string name) {

	if (currentProjects.count(name) == 1)
		currentProjects.erase(name);
	else
		finishedProjects.erase(name);
}
UserInfoManager::~UserInfoManager()
{
	for (std::map<std::string, Project*>::iterator itr = currentProjects.begin(); itr != currentProjects.end(); itr++)
	{
		delete (itr->second);
	}
	currentProjects.clear();

	for (std::map<std::string, Project*>::iterator itr = finishedProjects.begin(); itr != finishedProjects.end(); itr++)
	{
		delete (itr->second);
	}
	finishedProjects.clear();
	prerequisites.clear();
	StudyFields.clear();
}