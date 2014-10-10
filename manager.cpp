/*
 * manager.cpp
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#include "manager.h"
#include "info.h"

manager::manager(std::string log_filename) :
		log_filename_(log_filename), interval_(60), file_() {
	Run(true); // first time run
	StartLoop();
}

manager::~manager() {
	// TODO Auto-generated destructor stub

}

void manager::Run(bool first) {
	// creating new task
	auto new_task = std::make_shared<task>(info::GetCurrWorkspace());

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
	for (;;) {
		sleep(2); // XXX
		Run(false);
	}
}

bool manager::SaveTaskLog(const std::shared_ptr<task> tts) {
	// some asserts!!
	using namespace std;
	fstream file;
	file.open(log_filename_.c_str(), ios::in | ios::out | ios::app); // TODO: If can't open file
	if (!file.is_open()) {
		_erro("Can't open file: " << log_filename_);
		return false;
	}

	file << *tts << "\n";
	file.close();
	return true;
}

void manager::Save(std::shared_ptr<task> tts) {
	tasks_.push_back(tts);
	bool ok = file_.Save(*tts);
	assert(ok);
}
