/*
 * info.h
 *
 *  Created on: 7 paź 2014
 *      Author: abby
 */

#ifndef INFO_H_
#define INFO_H_

#include "libs.h"

class info {
public:
	info();
	virtual ~info();

	static std::string GetCurrWorkspace(); // uses wmctrl and awk
	static std::string GetCurrWin(); // FIXME: For some application (e.g xchat) c-string is NULL (works for e.g. chromium)
	static std::string Command(char *cmd); // executes bash command and return >>output<<

	static void Cut(std::string &s);

};

#endif /* INFO_H_ */
