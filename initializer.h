/*
 * initializer.h
 *
 *  Created on: 14 paź 2014
 *      Author: abby
 */

#ifndef INITIALIZER_H_
#define INITIALIZER_H_

#include "libs.h"

class initializer {
public:
	initializer();
	virtual ~initializer();

	void PrintHelp();
	void Run(const std::vector<std::string> &args);

private:
	bool Parse(const std::vector <std::string> &args);
	std::vector <std::string> SubVec(const size_t from, const std::vector <std::string> &fVec);
	void Run(const std::string &opt, const std::vector <std::string> &params);

	const static std::map <std::string, int> options;
	bool runFlag;

};

#endif /* INITIALIZER_H_ */
