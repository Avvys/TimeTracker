/*
 * manager.cpp
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#include "manager.h"
#include "info.h"

manager::manager() :
		interval_(60), file_() {
	_fact("start manager");

	Run(true); // first time run
	StartLoop();
}

manager::~manager() {
	// TODO Auto-generated destructor stub

}

void manager::Run(bool first) {
	// creating new task
	_dbg3("");
	auto new_task = std::make_shared<task>(info::GetCurrWorkspace());

	_dbg3("curr task: [" << *new_task << "]");

	if (first == true) {
		Save(new_task);
		return;
	}

	assert(tasks_.size());

	if (*new_task == *tasks_.back()) { // new task is the same as last -> continue
		_dbg1("continue task: " << *tasks_.back());
		new_task->setType(task::state::C);
		Save(new_task);
		if (que_tasks_.size())
			que_tasks_.pop_back(); // not needed
	} else if (que_tasks_.size() && *que_tasks_.back() == *new_task) {
		// in queue is the same task as now, we accept this task
		// create end task (name the same as last task in tasks_ vector
		_mark("new task: " << *new_task);
		_info("que: " << *que_tasks_.back());

		auto end_task = std::make_shared<task>(tasks_.back()->name_);
		end_task->setType(task::state::E);
		Save(end_task); // <--- end task to vector

		que_tasks_.pop_back();
		assert(!que_tasks_.size()); // queue should be empty

		Save(new_task); // <--- new task to vector
	} else {
		_fact("Task to que: " << *new_task);

		if (que_tasks_.size())
			que_tasks_.pop_back(); // not needed

		que_tasks_.push_back(new_task);
	}
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
		sleep(2); // XXX
		Run(false);
	}
}

void manager::Save(std::shared_ptr<task> tts) {
	_dbg3("saving task: " << *tts);
	tasks_.push_back(tts);
	bool ok = file_.Save(*tts);
	assert(ok);
}
