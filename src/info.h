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
	static std::string GetCurrWin(); // FIXME: For some application (e.g xchat) c-string is NULL (works for e.g. chromium) (not used for now)
	static std::pair <std::string, std::string> GetCurrWindow(); // https://github.com/UltimateHackingKeyboard/current-window-linux
	static std::string Command(std::string cmd); // executes bash command and return >>output<<
	static std::vector<std::string> splitString(std::string toSplit, std::string delimiter);

	static void Cut(std::string &s);

private:
	static Display *display;
	static unsigned long window;
	static unsigned char *prop;

	static void check_status(int status, unsigned long window);
	static unsigned char* get_string_property(std::string property_name);
	static unsigned long get_long_property(std::string property_name);



};

#endif /* INFO_H_ */
