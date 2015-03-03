/*
 * analyser.h
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#ifndef ANALYSER_H_
#define ANALYSER_H_

#include "libs.h"
#include "task.h"

class analyser {
public:
	analyser();
	virtual ~analyser();
	//void Timesheet(const std::string &filename); // prints details from *.tasks file

protected:
	virtual std::shared_ptr <task> LineToTask(const std::string &line); // converting line from file to task
	// eg. 2014-Oct-10 10:14:42 B ex -> task

	bool displayAll_;

	// struct for informations about task
	struct taskInfo {
		std::shared_ptr <task> ttask; // pointer to task, sometimes not used
		std::string name; // name of task
		boost::posix_time::ptime start_time;  // used only in timesheet mode
		boost::posix_time::ptime end_time; // used only in timesheet mode
		boost::posix_time::time_duration total_time;
		bool has_end; // used only in timesheet mode
		std::string memo; // not user for now
	};

	virtual void PrintOne(const std::shared_ptr<taskInfo> top) const; // prints taskInfo (not used at now)
	virtual bool ControlFile(const std::string &name) const; // return true if file exist, warningS if wrong extension;
};

#endif /* ANALYSER_H_ */
