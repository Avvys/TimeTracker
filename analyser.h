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

//namespace bprinter {
//	class TablePrinter;
//}

class analyser {
public:
	analyser(const std::string &filename);
	virtual ~analyser();
	void Timesheet(const std::string &filename);

private:
	void LineToTask(const std::string &line); // 2014-Oct-10 10:14:42 B ot
	std::vector <task>tasks_;

	struct taskInfo {
		std::shared_ptr <task> ttask;
		std::string name;
		boost::posix_time::ptime start_time;
		boost::posix_time::ptime end_time;
		boost::posix_time::time_duration total_time;
		bool has_end;
	};

	std::vector <std::shared_ptr<taskInfo>> taskInformations_;
	std::shared_ptr <task> ltask;

	void PrintOne(const std::shared_ptr<taskInfo> top) const;
	void PrintTable() const;
	void Correct();
};

#endif /* ANALYSER_H_ */
