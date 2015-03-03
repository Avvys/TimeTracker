/*
 * summary.h
 *
 *  Created on: 4 lis 2014
 *      Author: abby
 */

#ifndef SUMMARY_H_
#define SUMMARY_H_

#include "analyser.h"
#include "task.h"

// for logging
typedef boost::iostreams::tee_device<std::ostream, std::ofstream> TeeDevice;
typedef boost::iostreams::stream<TeeDevice> TeeStream;

class summary: protected analyser {
public:
	summary();
	summary(std::vector <std::string> fnames, bool da, bool log); // constructor for summary mode - print all tasks or daily
	//summary(std::vector <std::string> fnames); // logging mode - saves output to file (redirects cout stream)

	virtual ~summary();

private:
	void getFromFile(std::vector <std::string> &fnames); // getting data from file, creating submap
	void startLogging();
	void processTask(const std::shared_ptr<task> task_, std::map <std::string, taskInfo> &taskMap );
	// saving informations about task to submap or creating submap

	void merge();  // merge tasks and save them to map
	void addToMap(const std::shared_ptr<task> task_, std::map <std::string, taskInfo> &map); // adding task to given map
	void printMaps() const; // prints Map_ and submap
	void display(); // if displayAll is true, prints mergeMap_

	std::string createMap(const std::shared_ptr<task> task_with_diff_date); // new map fo task with different date, returns new date
	void formatName(std::string &name); // removes spaces and ":" from string
	std::string prepareForLogging();

	std::map <std::string, taskInfo> mergedMap_; // map with merged tasks from files
	std::vector <std::string> dates_;
	// contains date (as key) and map for every day
	// [ name ] [ map[name][taskInfo] ]
	std::map <std::string, std::map <std::string, taskInfo> > Map_;
	bool displayAll_; // display all task or daily
};

#endif /* SUMMARY_H_ */
