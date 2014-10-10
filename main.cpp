/*
 * main.cpp
 *
 *  Created on: 7 paź 2014
 *      Author: abby
 */

#include "libs.h"

#include "info.h"

#include "task.h"

#include "manager.h"
#include "analyser.h"

#include "tfile.h"

using namespace std;

int main() {
	cout << "test" << endl;
//	auto w = info::GetCurrWin();
//
	auto w2= info::GetCurrWorkspace();
	//cout << w2 << endl;
//	using namespace boost::posix_time;
//
//
//	auto now =  second_clock::local_time();
//
//	enum os {linux, spple, win};
//
//	os my = linux;
//	ostringstream oss; oss << my ;
//
//	cout << oss.str() << endl;
//	auto today = now.date();

//	manager TimeTracker("log.txt");
//	//TimeTracker.Run();
//	TimeTracker.Display();

	const string test = "log/2014-Oct-10";
	analyser A(test);


}
