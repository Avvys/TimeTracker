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
#include "tfile.h"

class manager {
public:
	manager();
	virtual ~manager();

	void Run(bool first); // creates new task
	void Display();
	void StartLoop();

private:
	void Save(std::shared_ptr<task> tts);

	std::vector <std::shared_ptr<task>> tasks_;
	std::vector <std::shared_ptr<task>> que_tasks_;
	size_t interval_;
	tfile file_;
};

#endif /* MANAGER_H_ */
