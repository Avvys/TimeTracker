/*
 * tfile.cpp
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#include "tfile.h"
#include "info.h"
tfile::tfile() :
		time_date_(boost::posix_time::second_clock::local_time()), dir_name_(
				"log") {

	using namespace boost::posix_time;

	name_ = to_iso_extended_string(time_date_).substr(0, 10);

	path_ = dir_name_ + "/" + name_;

	_info("filename will be: [" << name_ <<"]"); // TODO month as number

	if (!FileExist(dir_name_))
		assert(boost::filesystem::create_directory(dir_name_));
}

tfile::~tfile() {
	_dbg2("Destructing tfile");
}

bool tfile::Save(const task& t) {
	using namespace std;
	fstream file;
	file.open(path_.c_str(), ios::in | ios::out | ios::app);
	if (!file.is_open())
		return false;
	_info("saving " << t);
	file << t << "\n";
	return true;
}

bool tfile::FileExist(const std::string &filename) {
	return boost::filesystem::exists(filename);
}

std::string tfile::Getline() {
}
