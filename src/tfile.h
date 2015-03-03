/*
 * tfile.h
 *
 *  Created on: 10 paź 2014
 *      Author: abby
 */

#ifndef TFILE_H_
#define TFILE_H_

#include "libs.h"
#include "task.h"

class tfile {
public:
	tfile();
	virtual ~tfile();
	bool Save(const task &t);
	bool FileExist(const std::string &filename);
	std::string Getline();

private:
	boost::posix_time::ptime time_date_;
	std::string name_;
	std::string dir_name_;
	std::string path_;
};

#endif /* TFILE_H_ */
