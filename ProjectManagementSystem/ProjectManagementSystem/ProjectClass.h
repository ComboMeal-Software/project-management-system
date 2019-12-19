// Project Class header file
// It contains the abstract class and two derived Project classes (Mandatory and Optional)

#ifndef PROJECTCLASS_H
#define PROJECTCLASS_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Project //Abstract
{
private:
	string name;
	string objective;
	string tasks;
	string subjectField;
	string client;
	vector<string> Prerequisites;
	//StatusManager* status;
	//DeadlineManager* deadline;
	//User* pnitiator;
	//User* panager;
	//map<string, User*> participants;
	// --Private methods--
	void setStatus(string status);
	void setClient(string client);
	//void setManager(User &client);
	void setDeadline(string deadline);
	void setObjective(string objective);
	void setTasks(string tasks);
	void setSubjectField(string subjectField);
	void addPrerequisites(string prerequisites);
	//virtual void addParticipant(User& participant) = 0; //Pure virtual method!
public:
	void findParticipants();
	void changeInfo();
	//User* getInitiator();
	string getClient();
	//User* getManager();
	//map<string, User*> participants;
	string getSubjectField();
	string getName();
	string getObjective();
	string getTasks();
	string getDeadline();
	vector<string> getPrerequisites();
	string getStatus();
	friend ostream& operator<<(ostream& os, const Project& pr);
};

class MandatoryProject : Project {
private:
	//void addParticipant(User& participant);
public:
	//MandatoryProject(User& initiator, string name, string objective, string tasks, string subjectField, string deadline, string prerequisites);
	//~MandatoryProject(); //Gotta work on this
};

class OptionalProject : Project {
private:
	//void addParticipant(User& participant);
public:
	//OptionalProject(User& initiator, string name, string objective, string tasks, string subjectField, string deadline, string prerequisites);
	//~OptionalProject(); //Gotta work on this
};

#endif