/*
 * initializer.h
 *
 *  Created on: 14 paź 2014
 *      Author: abby
 */

#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#include "libs.h"

typedef std::vector<std::string> pair_;

class initializer {
public:
	initializer();
	virtual ~initializer();

	void PrintHelp();
	void Run(const std::vector<std::string> &args);

private:
	bool Parse(const std::vector<std::string> &args);
	std::vector<std::string> SubVec(const size_t from, const std::vector<std::string> &fVec);
	void Run(const std::string &opt, const std::vector<std::string> &params);

	const static std::map < std::string, pair_> options;
	// map of options
	//  { { command, description } , number of params }
	// eg. ./TimeTracker -a <one-file>

	bool runFlag;

};

#endif /* INITIALIZER_H_ */
