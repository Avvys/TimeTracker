/*
 * task.h
 *
 *  Created on: 7 paź 2014
 *      Author: abby
 */

#ifndef TASK_H_
#define TASK_H_

#include "libs.h"

class task {
public:
	enum state {
		B, C, E
	}; // state of task: beginn, continue, end
	static const std::vector<std::string> states_;

	task(std::string name);
	task(const std::string &day_time, const std::string &type, const std::string &name);
	// operators
	friend std::ostream& operator<<(std::ostream &out, const task &ctask) ; // 2014-Oct-10 10:14:42 B ot
	bool operator==(const task& task1) const {
		return (task1.name_ == name_);
	}
	bool operator!=(const task& task1) const {
		return !(task1.name_ == name_);
	}

	virtual ~task();

	state getType() const {
		return type_;
	}

	void setType(state type);

	// are public because const
	const std::string name_;
	const boost::posix_time::ptime day_time_;

private:
	state type_;



};

#endif /* TASK_H_ */
