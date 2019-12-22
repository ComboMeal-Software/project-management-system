#include "Database.h"

#include "UserClass.h"
#include "ProjectClass.h"

void Database::createUser(std::string name, std::string password, int free_time, std::string prerequisites, std::string StudyFields)
{
	users.emplace(std::pair<std::string, User*>(name, new User(name, password, free_time, prerequisites, StudyFields)));
}

void Database::createProject(User* initiator, std::string name, std::string objective, std::string tasks, std::string subjectField, std::string client, std::string deadline, std::string prerequisites)
{
	projects.emplace(std::pair<std::string, Project*>(name, new Project(initiator, name, objective, tasks, subjectField, client, deadline, prerequisites)));
}

User* Database::getUser(std::string name)
{
	return users[name];
}

void Database::deleteUser(std::string userName)
{
	delete users[userName];
	users.erase(userName);
}

void Database::deleteProject(std::string projectName)
{
	delete projects[projectName];
	projects.erase(projectName);
}

void Database::finishProject(std::string projectName)
{
	finishedProjects.insert(std::pair<std::string, Project*>(projectName, projects[projectName]));
	projects.erase(projectName);
}

std::vector<Project*> Database::findProjects(std::vector<std::string> prer)
{
	std::vector<Project*> found;
	bool flag = false;
	std::vector<std::string> projectPrer;
	for (const std::pair<std::string, Project*>& p : projects)
	{
		projectPrer = p.second->getPrerequisites();
		for (int i = 0; i < projectPrer.size(); i++)
		{
			flag = false;
			for (int j = 0; j < prer.size(); j++)
			{
				if (prer[j] == projectPrer[i])
				{
					flag = true;
					break;
				}
			}
			if (flag == false)
			{
				break;
			}
		}
		if (flag == true)
		{
			found.push_back(p.second);
		}
	}
}

std::vector<User*> Database::findParticipants(std::vector<std::string> prer)
{
	std::vector<User*> found;
	bool flag = false;
	std::vector<std::string> userPrer;
	for (const std::pair<std::string, User*>& p : users)
	{
		userPrer = p.second->getPrerequisites();
		for (int i = 0; i < userPrer.size(); i++)
		{
			flag = false;
			for (int j = 0; j < prer.size(); j++)
			{
				if (prer[j] == userPrer[i])
				{
					flag = true;
					break;
				}
			}
			if (flag == false)
			{
				break;
			}
		}
		if (flag == true)
		{
			found.push_back(p.second);
		}
	}
}