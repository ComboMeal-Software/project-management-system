// UserInfoManager Class header file
//

#pragma once
#ifndef USERINFOMANAGERCLASS_H
#define	USERINFOMANAGERCLASS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

class User;
class Project;

class UserInfoManager {
private:
	std::string name;
	std::string password;
	int freetime;
	std::map<std::string, Project*> currentProjects;
	std::map<std::string, Project*> finishedProjects;
	std::vector<std::string> prerequisites;
	std::vector<std::string> StudyFields;
public:
	UserInfoManager();
	void setName(std::string name);
	void changePassword(std::string pass);
	void changeFreetime(int time);
	void addCurrentProjects(Project& project);
	void addFinishedProjects(Project& project);
	void addPrerequisites(std::string prerequisite);
	void addStudyFields(std::string StudyFields);
	void deleteProject(std::string name);
	std::string getName();
	int getFreetime();
	std::map<std::string, Project*> getCurrentProjects();
	std::map<std::string, Project*> getFinishedProjects();
	std::vector<std::string> getPrerequisites();
	std::vector<std::string> getStudyFields();
	bool checkPassword(std::string pass);
	~UserInfoManager();
};


#endif // !USERINFOMANAGERCLASS_H
