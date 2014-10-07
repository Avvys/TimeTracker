/*
 * manager.cpp
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#include "manager.h"
#include "info.h"

manager::manager(std::string log_filename) :
		log_filename_(log_filename), interval_(60) {
	// TODO Auto-generated constructor stub
	auto new_task = std::make_shared<task>(info::GetCurrWorkspace());
	tasks_.push_back(new_task);
	StartLoop();
}

manager::~manager() {
	// TODO Auto-generated destructor stub

}

void manager::Run(bool first) {
	// creating new task
	auto new_task = std::make_shared<task>(info::GetCurrWorkspace());
	if(first==true) {
		tasks_.push_back(new_task);
		return;
	}

	assert(tasks_.size());

	if (*new_task == *tasks_.back()) { // new task is the same as last -> continue
		new_task->setType(task::state::C);
	} else { // change last task to end state and begin new tag
		tasks_.back()->setType(task::state::E);
	}
	tasks_.push_back(new_task);

	Display();
}

void manager::Display() {
	assert(tasks_.size());
	std::cout << "\n=========================" << std::endl;
	for (auto tmp : tasks_)
		std::cout << *tmp << std::endl;
	std::cout << "=========================" << std::endl;
}

void manager::StartLoop() {
	for(; ;) {
		sleep(1); // XXX
		Run(false);
	}
}

void manager::SaveTaskLog() {
//	using namespace std;
//	fstream file;
//	file.open(log_filename_.c_str(), ios::in | ios::out); // TODO: If can't open file
//
//	file << tts << "\n";
//
//	file.close;
}

void manager::FirstRun() {
}
