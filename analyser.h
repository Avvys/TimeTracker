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
	analyser(const std::string &filename);
	virtual ~analyser();
	void Timesheet(const std::string &filename);

private:
	void LineToTask(const std::string &line); // 2014-Oct-10 10:14:42 B ot
	std::vector <task>tasks_;

	struct taskInfo {
		std::shared_ptr <task> ttask;
		boost::posix_time::ptime start_time;
		boost::posix_time::ptime end_time;
		// some period
		bool has_end;
	};

	std::vector <std::shared_ptr<taskInfo>> taskInformations_;

	void PrintOne(const std::shared_ptr<taskInfo> top) const;
};

#endif /* ANALYSER_H_ */
