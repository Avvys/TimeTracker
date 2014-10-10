/*
 * task.cpp
 *
 *  Created on: 7 paź 2014
 *      Author: abby
 */

#include "task.h"

using namespace boost::posix_time;

const std::vector<std::string> task::states_ = { "B", "C", "E" };

task::task(std::string name) :
		name_(name), day_time_(second_clock::local_time()), type_(B) {
}

std::ostream& operator<<(std::ostream& os, const task& ctask) {
	os << ctask.day_time_ << " " << task::states_.at(ctask.type_) << " "
			<< ctask.name_;
}

task::~task() {
	// TODO Auto-generated destructor stub
	_dbg2("Destructing task " << name_);
}

void task::setType(state type) {
	if (type == B)
		throw std::invalid_argument("New state must be continue or end!");
	type_ = type;
	_dbg2("type changed to: " << states_.at(type));
}

task::task(const std::string &day_time, const std::string &type,
		const std::string &name) :
		name_(name), day_time_(time_from_string(day_time)) {
	using namespace std;
	const auto it = find(states_.begin(), states_.end(), type);
	const auto pos = it - states_.begin();
	type_ = static_cast<state>(pos);
}
