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

/***
@brief this class checks manages the program main function: checks the activity, stores it, runs main loop
*/
class manager {
public:
	manager();
	virtual ~manager();

	void Run(bool first); ///< creates new task
	void Display();
	void StartLoop(); ///< enters (and remains untill end) in the main program loop (of the time tracker mode)

private:
	void Save(std::shared_ptr<task> tts);
	bool CheckPeriod(std::shared_ptr<task> tts, std::shared_ptr<task> prev);

	void CreateContinueTask(std::shared_ptr<task> new_task);
	void CreateEndTask(std::shared_ptr<task> new_task);

	std::vector <std::shared_ptr<task>> tasks_;
	std::vector <std::shared_ptr<task>> que_tasks_;
		/// low: less responsive, high: higher cpu use (but anyway will be negligable)
	int interval_test_; ///< in seconds, how often do we (fully) test current situation like desktop name (and main loop run step).
	int interval_continue_; ///< in seconds, how often do we write to store the current task that it is continued.
	int interval_change_grace_; ///< in seconds, grace period for desktop change
	tfile file_;
};

#endif /* MANAGER_H_ */
