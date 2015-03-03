/*
 * timesheet.cpp
 *
 *  Created on: 4 lis 2014
 *      Author: abby
 */

#include "timesheet.h"

timesheet::timesheet(const std::string &filename) {
	_info(filename);
	if (ControlFile(filename))
		getFromFile(filename);
}

timesheet::~timesheet() {
	// TODO Auto-generated destructor stub
}

void timesheet::getFromFile(const std::string& filename)	{
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
		if (a == "") break;
		process(a);
	}

	correct();
	printTable();
}

void timesheet::process(const std::string& line) {
	auto new_task = LineToTask(line);
	const auto type = new_task->getType();

	if (type == task::state::B) { // if new task has type "begin" create new info struct
		correct();
		createTaskInfo(new_task);
	}
	else if (type == task::state::E) { // end - save ending time to struct
		completeTaskInfo(new_task);
	}
	ltask = new_task;
}

void timesheet::correct() {
	if (taskInformations_.empty()) return; // nothing to do
	if (taskInformations_.back()->has_end) return; // nothing to do

	_info("correcting");
	taskInformations_.back()->end_time = ltask->day_time_;
	taskInformations_.back()->total_time = taskInformations_.back()->end_time
			- taskInformations_.back()->start_time;
	taskInformations_.back()->has_end = true;
}

void timesheet::printTable() const {
	using namespace std;
	using namespace boost::posix_time;
	string sep;
	sep.assign(46,'-');
	sep.at(0) = '+';

	for (auto ttask : taskInformations_) {
		const auto st = to_iso_extended_string(ttask->start_time).substr(11, 18);
		const auto et = to_iso_extended_string(ttask->end_time).substr(11, 18);
		cout << sep << endl;
		cout << "| " << setw(12) << ttask->name << " | " << st << " " << et << " " << ttask->total_time << " \n";
		//cout << "| " << setw(12) << "programs: "<< " | "<< endl;
		cout << sep << endl << endl;
	}
}

void timesheet::createTaskInfo(const std::shared_ptr<task>& new_task) {
	auto task_info = std::make_shared<taskInfo>();
	task_info->name = new_task->name_;
	task_info->ttask = new_task;
	task_info->start_time = new_task->day_time_;
	task_info->has_end = false;
	taskInformations_.push_back(task_info);
}

void timesheet::completeTaskInfo(const std::shared_ptr<task>& new_task) {
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
	taskInformations_.back()->total_time =
			taskInformations_.back()->end_time
					- taskInformations_.back()->start_time;
//		PrintOne(taskInformations_.back());
}
