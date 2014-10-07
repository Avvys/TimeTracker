/*
 * manager.h
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "libs.h"
#include "task.h"

class manager {
public:
	manager(std::string log_filename);
	virtual ~manager();

	void Run(bool first);
	void Display();
	void StartLoop();

private:
	void SaveTaskLog();
	void FirstRun(); // just creates new task add add to vector, no assert


	std::vector <std::shared_ptr<task>> tasks_;
	std::string log_filename_;
	size_t interval_;
};

#endif /* MANAGER_H_ */
