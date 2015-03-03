/*
 * detecttest.cpp
 *
 *  Created on: 7 lis 2014
 *      Author: abby
 */

#include "detecttest.h"
#include "../libs.h"
#include "../info.h"

detect_test::detect_test()
{
	_info("running test");
	auto ok = detectWindow();
	_dbg3(ok);
}

detect_test::~detect_test()
{
	// TODO Auto-generated destructor stub
}

bool detect_test::detectWindow() {
	bool ok = false;
	while (true) {
		sleep(2);
		auto win = info::GetCurrWindow();
		if (win.first == "" || win.second == "") {
			_erro("not detected");
			ok = false;
		}
		else {
			_dbg2(win.first << " - " << win.second);
			ok = true;
		}
		_dbg1("workspace: " << info::GetCurrWorkspace());
	}
	return ok;
}

bool detect_test::detectWorkspace() {
	return true;
}
