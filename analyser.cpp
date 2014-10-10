/*
 * analyser.cpp
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#include "analyser.h"

analyser::analyser(const std::string& filename) {
	bool e = boost::filesystem::exists(filename);
	_fact(filename);
	if (e)
		Timesheet(filename);

}

analyser::~analyser() {
	// TODO Auto-generated destructor stub
}

void analyser::Timesheet(const std::string& filename) {
	using namespace std;
	fstream file;
	file.open(filename.c_str(), ios::in | ios::out);
	if (!file.is_open()) {
		_erro("Can't open file " << filename);
		return;
	}

	while (!file.eof()) {
		string a;
		getline(file, a);

		if(a == "") break;
		LineToTask(a);
	}
}

void analyser::LineToTask(const std::string& line) {
	using namespace boost::posix_time;
	const auto splited = nOT::nUtils::SplitString(line);
	assert(splited.size() == 4);
	for (auto tmp : splited)
		_dbg1(tmp);

	// format:
	//	   [0]            [1]      [2]   [3]
	//	2014-Oct-10		16:19:43	C	task

	auto new_task = std::make_shared<task>(splited.at(0) + " " + splited.at(1),
			splited.at(2), splited.at(3));

	// only for test - is creating task the same as line?
	std::ostringstream oss;
	oss << *new_task;

	assert(line == oss.str());

	const auto type = new_task->getType();

	if (type == task::state::B) { // if new task has type "begin" create new info struct
		auto task_info = std::make_shared<taskInfo>();
		task_info->ttask = new_task;
		task_info->start_time = new_task->day_time_;
		task_info->has_end = false;
		taskInformations_.push_back(task_info);
	} else if (type == task::state::E) { // end - save ending time to struct
		const auto stru = taskInformations_.back();
		const auto ttask = stru->ttask;
		if (*new_task != *ttask) {
			_erro(
					"Critical! End task without beginning!: end_task " << ttask->name_ << "; new_task: " << new_task->name_);
			return;
		}
		// all ok
		taskInformations_.back()->end_time = new_task->day_time_;
		taskInformations_.back()->has_end = true;

		PrintOne(taskInformations_.back());
// print nice tabl
	}

}

void analyser::PrintOne(const std::shared_ptr<taskInfo> top) const {
	_mark(*top->ttask);
}
