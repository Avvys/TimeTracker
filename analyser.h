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
//#include "timesheet.h"

// for logging
typedef boost::iostreams::tee_device<std::ostream, std::ofstream> TeeDevice;
typedef boost::iostreams::stream<TeeDevice> TeeStream;

class analyser {
public:
	analyser();
	analyser(std::vector <std::string> fnames, bool da); // constructor for summary mode - print all tasks or daily
	analyser(std::vector <std::string> fnames); // logging mode - saves output to file (redirects cout stream)

	virtual ~analyser();
	//void Timesheet(const std::string &filename); // prints details from *.tasks file

protected:
	virtual std::shared_ptr <task> LineToTask(const std::string &line); // converting line from file to task
	// eg. 2014-Oct-10 10:14:42 B ex -> task

	virtual void SummaryGetFromFile(std::vector <std::string> &fnames); // getting data from file, creating submap
	//void TimesheetProcess(const std::string &line); // 2014-Oct-10 10:14:42 B ot

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

	// saving informations about task to submap or creating submap
	void SummaryProcessTask(const std::shared_ptr<task> task_, std::map <std::string, taskInfo> &taskMap );

	std::map <std::string, taskInfo> mergedMap_; // map with merged tasks from files

	void Merge(); // merge tasks and save them to map

	// contains date (as key) and map for every day
	// [ name ] [ map[name][taskInfo] ]
	std::map <std::string, std::map <std::string, taskInfo> > Map_;


	const bool displayAll_; // display all task or daily

	void AddMap(const std::shared_ptr<task> task_, std::map <std::string, taskInfo> &map); // adding task to given map
	void PrintOne(const std::shared_ptr<taskInfo> top) const; // prints taskInfo (not used at now)

	void PrintMaps() const; // prints Map_ and submap
	void Display(); // if displayAll is true, prints mergeMap_

	virtual bool ControlFile(const std::string &name) const; // return true if file exist, warningS if wrong extension;
};

#endif /* ANALYSER_H_ */
