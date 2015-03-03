/*
 * timesheet.h
 *
 *  Created on: 4 lis 2014
 *      Author: abby
 */

#ifndef TIMESHEET_H_
#define TIMESHEET_H_

#include "libs.h"
#include "task.h"
#include "analyser.h"

class timesheet : protected analyser {
public:
	timesheet(const std::string &filename);
	virtual ~timesheet();

private:
	void getFromFile(const std::string &filename);
	void process(const std::string &line);
	void correct(); // fot timesheet mode: corrects informations
	void printTable() const; // Timesheet - print taskInfos
	void createTaskInfo(const std::shared_ptr<task> &new_task);
	void completeTaskInfo(const std::shared_ptr<task> &new_task);
	// stores pointers to informations about tasks (timesheet mode)
	std::vector <std::shared_ptr<taskInfo>> taskInformations_;

	// last task loaded from file (timesheet mode)
	std::shared_ptr <task> ltask;
};

#endif /* TIMESHEET_H_ */
