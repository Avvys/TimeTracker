/*
 * analyser.cpp
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#include "analyser.h"

analyser::analyser() : displayAll_(false) {
	_dbg3("constructor");
}

analyser::~analyser() {
	// TODO Auto-generated destructor stub
}

std::shared_ptr<task> analyser::LineToTask(const std::string &line) {
	using namespace boost::posix_time;
	const auto splited = nOT::nUtils::SplitString(line);
	assert(splited.size() == 4);
	//	for (auto tmp : splited)
	//		_dbg3(tmp);

	// format:
	//     [0]             [1]      [2]   [3]
	//	2014-Oct-10		16:19:43	C	  task

	// splited.at(2) must be type of task
	assert(splited.at(2) == "B" || splited.at(2) == "C" || splited.at(2) == "E");

	auto new_task = std::make_shared<task>(splited.at(0) + " " + splited.at(1),
			splited.at(2), splited.at(3));

	// only for test - is creating task the same as line?
	std::ostringstream oss;
	oss << *new_task;

	assert(line == oss.str());
	return new_task;
}

void analyser::PrintOne(const std::shared_ptr<taskInfo> top) const {
	_mark(*top->ttask);
	_dbg1(top->total_time);
}

bool analyser::ControlFile(const std::string& name) const {
	bool e = boost::filesystem::exists(name);
	if(!e) _erro("File [" << name <<"] doesn't exist!" );

	if(name.find(".task")==std::string::npos)
		_warn("File: [" << name << "] has wrong extension, trying to read them");

	return e;
}
