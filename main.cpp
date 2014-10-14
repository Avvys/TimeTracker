/*
 * main.cpp
 *
 *  Created on: 7 paź 2014
 *      Author: abby
 */

#include "libs.h"
#include "initializer.h"

using namespace std;

int main(int argc, char *argv[]) {
	_info("start");

	vector<string> args(argv, argv + argc); // convert arguments to vector

	initializer timeTracker;
	timeTracker.Run(args);
}
