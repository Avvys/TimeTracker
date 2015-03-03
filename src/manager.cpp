/*
 * manager.cpp
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#include "manager.h"
#include "info.h"

manager::manager() :
		interval_test_(2),
				interval_continue_(10),
				interval_change_grace_(6),
				file_()
{
	_fact("start manager, interval_test_="<<interval_test_);

	assert(interval_test_ <= interval_continue_);
	assert(interval_test_ <= interval_change_grace_);

	_dbg3("interval continue: " << interval_continue_);
	_dbg3("interval change grace: " << interval_change_grace_);

	Run(true); // first time run
	StartLoop();
}

manager::~manager() {
// TODO Auto-generated destructor stub
}

void manager::Run(bool first) {
	// creating new task
	_dbg1("creating new task");
	auto new_task = std::make_shared<task>(info::GetCurrWorkspace());

	_dbg3("curr task: [" << *new_task << "]");

	if (first == true) { // first task - just save them
		Save(new_task);
		return;
	}

	assert(tasks_.size());

	if (*new_task == *tasks_.back()) { // new task is the same as last -> continue
		CreateContinueTask(new_task);
	}
	else if (que_tasks_.size() && *que_tasks_.back() == *new_task && CheckPeriod(new_task, tasks_.back())) { // new task
	// in queue is the same task as now, we accept this task
	// create end task (name the same as last task in tasks_ vector
	// interval_change_grace_
		CreateEndTask(new_task);
	}
	else {
		_fact("Task to que: " << *new_task);

		if (que_tasks_.size()) que_tasks_.pop_back(); // not needed

		que_tasks_.push_back(new_task);
	}
}

void manager::CreateContinueTask(std::shared_ptr<task> new_task) {
	_dbg1("continue task: " << *new_task);
	new_task->setType(task::state::C);
	Save(new_task); // <--- saving here
	if (que_tasks_.size())
	que_tasks_.pop_back(); // not needed
}

void manager::CreateEndTask(std::shared_ptr<task> new_task) {
	_mark("new task: " << *new_task);
	_info("que: " << *que_tasks_.back());

	auto end_task = std::make_shared<task>(tasks_.back()->name_);
	end_task->setType(task::state::E);

	que_tasks_.pop_back();

	assert(!que_tasks_.size()); // queue should be empty

	Save(end_task); // <--- saving here
	Save(new_task); // <--- saving here
}

void manager::Display() {
	assert(tasks_.size());
	std::cout << "\n=========================" << std::endl;
	for (auto tmp : tasks_)
		std::cout << *tmp << std::endl;
	std::cout << "=========================" << std::endl;
}

void manager::StartLoop() {
	_info("inf loop");
	for (;;) {
		sleep(interval_test_); // XXX config
		Run(false);
	}
}

void manager::Save(std::shared_ptr<task> tts) {
	_dbg3("saving task: " << *tts);
	tasks_.push_back(tts);
	bool ok = file_.Save(*tts);
	assert(ok);
}

bool manager::CheckPeriod(std::shared_ptr<task> tts, std::shared_ptr<task> prev) {
	using namespace boost::posix_time;
	const auto p = tts->day_time_ - prev->day_time_;
	const time_duration icg = seconds(interval_change_grace_);

	_info("time diff: " << p << "; interval: " << icg);

	if (p < icg) return false;
	else
		return true;
}
