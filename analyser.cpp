/*
 * analyser.cpp
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#include "analyser.h"
#include "bprinter/table_printer.h"
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

		if (a == "")
			break;
		LineToTask(a);
	}
	Correct();
	PrintTable();
}

void analyser::LineToTask(const std::string& line) {
	using namespace boost::posix_time;
	const auto splited = nOT::nUtils::SplitString(line);
	assert(splited.size() == 4);
//	for (auto tmp : splited)
//		_dbg3(tmp);

	// format:
	//     [0]             [1]      [2]   [3]
	//	2014-Oct-10		16:19:43	C	task

	auto new_task = std::make_shared<task>(splited.at(0) + " " + splited.at(1),
			splited.at(2), splited.at(3));

	// only for test - is creating task the same as line?
	std::ostringstream oss;
	oss << *new_task;

	assert(line == oss.str());

	const auto type = new_task->getType();

	if (type == task::state::B) { // if new task has type "begin" create new info struct
		Correct();
		auto task_info = std::make_shared<taskInfo>();
		task_info->name = new_task->name_;
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
		taskInformations_.back()->total_time =
				taskInformations_.back()->end_time
						- taskInformations_.back()->start_time;

//		PrintOne(taskInformations_.back());

	}
	ltask=new_task;
}

void analyser::PrintOne(const std::shared_ptr<taskInfo> top) const {
	_mark(*top->ttask);
	_dbg1(top->total_time);
}

void analyser::PrintTable() const {
	using namespace std;
	using namespace boost::posix_time;
	for (auto ttask : taskInformations_) {
		const auto st = to_iso_extended_string(ttask->start_time).substr(11,18);
		const auto et = to_iso_extended_string(ttask->end_time).substr(11,18);

		cout << setw(10) <<ttask->name << " | " << st << " "<< et << " "<<  ttask->total_time << " \n";
	}
}

void analyser::Correct() {
	if(taskInformations_.empty()) return;
	if(taskInformations_.back()->has_end) return;

	_info("correcting");
	taskInformations_.back()->end_time = ltask->day_time_;
	taskInformations_.back()->total_time = taskInformations_.back()->end_time
			- taskInformations_.back()->start_time;
	taskInformations_.back()->has_end = true;

}
