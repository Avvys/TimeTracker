/*
 * summary.cpp
 *
 *  Created on: 4 lis 2014
 *      Author: abby
 */

#include "summary.h"

summary::summary() :
		displayAll_(false)
{
	// TODO Auto-generated constructor stub

}

summary::summary(std::vector<std::string> fnames, bool da, bool log) :
		displayAll_(da) {
	bool ok = false;
	for (auto fn : fnames)
		if (ControlFile(fn)) ok = true;

	assert(ok);
	getFromFile(fnames);

	if (log) startLogging();
	else display();
}
void summary::formatName(std::string& name) {
	// no spaces and :
	name.replace(name.find(" "), 1, "-");
	size_t control = std::string::npos;
	while (control != std::string::npos) {
		control = name.find(":");
		name.replace(control, 1, " ");
	}
	assert(name.find(" ") == std::string::npos);
	_mark(name);
}

std::string summary::prepareForLogging() {
	displayAll_ = true;
	const std::string dir = "data/";

	// preparing logname
	using namespace std;
	const auto tdate = boost::posix_time::second_clock::local_time();
	ostringstream oss;
	oss << "OUT-" << tdate << ".txt";
	string logname = dir + oss.str();

	formatName(logname);

	// directory for logs
	if (!boost::filesystem::exists(dir)) assert(boost::filesystem::create_directory(dir));

	assert(!boost::filesystem::exists(logname));
	return logname;
}

void summary::startLogging() {
	using namespace std;
	const auto logname = prepareForLogging();

	// redirecting cout stream
	// http://coliru.stacked-crooked.com/a/9c4729dd796c5daf
	ofstream logFile;
	logFile.open(logname.c_str());
	ostream tmp(cout.rdbuf());
	TeeDevice outputDevice(tmp, logFile); // <----
	TeeStream logger(outputDevice);

	cout.rdbuf(logger.rdbuf());

	// printing
	printMaps();
	cout << "\t == ALL ==" << endl;
	display();

	logger.close();
}

summary::~summary() {
	// TODO Auto-generated destructor stub
}

void summary::getFromFile(std::vector<std::string>& fnames) {
	using namespace std;
	sort(fnames.begin(), fnames.end());

	for (auto fname : fnames) {
		_dbg2(fname);
		fstream file;
		file.open(fname.c_str(), ios::in | ios::out);

		if (!file.is_open()) // can't open file, nothing to do
		_warn("Can't open file " << fname);

		else { // file is open
			string lastTaskDate = "";

			// reading file
			while (!file.eof()) {
				string a = "";
				getline(file, a);
				if (a == "") break; // no data = break loop

				auto tmp_task = LineToTask(a);
				assert(tmp_task->dateToString() != "");

				// if current task is first or has different date than previous, create new map for this task
				if (lastTaskDate != tmp_task->dateToString() || lastTaskDate == "") lastTaskDate = createMap(tmp_task);

				processTask(tmp_task, Map_.at(lastTaskDate));
			}
		}
	}
}

std::string summary::createMap(const std::shared_ptr<task> task_with_diff_date) {
	using namespace std;
	const auto task_date = task_with_diff_date->dateToString();
	taskInfo tstruct;
	map<string, taskInfo> dMap;
	Map_.insert(std::pair<std::string, std::map<std::string, taskInfo> >(task_date, dMap));
	return task_date;
}

void summary::processTask(const std::shared_ptr<task> task_, std::map<
		std::string, taskInfo>& taskMap) {
	const auto tname = task_->name_;
	auto it = taskMap.find(tname); // exist element with key tname?
	if (it == taskMap.end()) { // not found, create them, nothing to do
		addToMap(task_, taskMap);
		return;
	}

	// saving informations
	auto &tinfo = it->second;
	auto &start_time = tinfo.start_time;
	auto &curr_time = task_->day_time_;
	tinfo.total_time = curr_time - start_time;
}

void summary::merge() {
	using namespace std;
	assert(!Map_.empty());

	for (auto &it1 : Map_) {
		dates_.push_back(it1.first);
		for (auto& it : it1.second) {
			auto found = mergedMap_.find(it.first);

			if (found == mergedMap_.end())
			mergedMap_.insert(pair<string, taskInfo>(it.first, it.second));
			else {
				mergedMap_.at(it.first).total_time += it.second.total_time;
			}
		}
	}
}

void summary::addToMap(const std::shared_ptr<task> task_, std::map<std::string,
		taskInfo>& map) {
	const auto name = task_->name_;
	taskInfo tstruct;
	tstruct.name = name;
	tstruct.start_time = task_->day_time_;

	map.insert(std::pair<std::string, taskInfo>(name, tstruct));
}

void summary::printMaps() const {
	using namespace std;
	const string sep = "+-----------------------------------";

	for (auto &it1 : Map_) {
		cout << "\t" << it1.first << endl;
		for (auto& it : it1.second) {
			cout << sep << endl;
			cout << "| Name: | " << it.first << endl;
			cout << "| Time: | " << it.second.total_time << endl;
		}
		cout << sep << endl;
		cout << endl;
	}
}

void summary::display() {
	if (!displayAll_) {
		printMaps();
		return;
	}
	using namespace std;
	merge();
	assert(!dates_.empty());

	cout << "\tDays: " << endl;
	for (auto day : dates_)
		cout << day << endl;

	const string sep = "+-----------------------------------";

	for (auto& it : mergedMap_) {
		cout << sep << endl;
		cout << "| Name: | " << it.first << endl;
		cout << "| Time: | " << it.second.total_time << endl;
	}
	cout << sep << endl;
	cout << endl;
}
