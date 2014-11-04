/*
 * info.cpp
 *
 *  Created on: 7 paź 2014
 *      Author: abby
 */

#include "info.h"

using namespace std;

info::info() {
	// TODO Auto-generated constructor stub

}

info::~info() {
	// TODO Auto-generated destructor stub
}

string info::GetCurrWorkspace() {
	auto w = Command(" wmctrl -d | grep \"*\" | awk \'{print $10 }\'"); // TODO better way to get workspace name
	assert(w!="ERROR");
	w.pop_back();
	return w;
}

std::string info::GetCurrWin() {
	Display *display;
	Window focus;
	char *window_name;
	int revert;

	display = XOpenDisplay(NULL);
	XGetInputFocus(display, &focus, &revert);
	XFetchName(display, focus, &window_name);

	cout << "tittle: " << window_name << endl;

	if (window_name) {
		const string win_name(window_name);
		return win_name;
	} else
		return "";
}

std::string info::Command(char* cmd) {
	FILE* pipe = popen(cmd, "r");
	if (!pipe)
		return "ERROR";
	char buffer[128];
	std::string result = "";
	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;

}

void info::Cut(std::string& s) {
	auto v = nOT::nUtils::SplitString(s);
	s=v.at(0);
}
vector<string> info::splitString(string toSplit, string delimiter) {
    assert(toSplit != "");
    assert(delimiter != "");

	if(nOT::nUtils::ToStr(toSplit.back()) != delimiter)
    	toSplit+=delimiter;

    string token;
    size_t pos = 0;
    vector<string> data;

    while ((pos = toSplit.find(delimiter)) != string::npos) {
        token = toSplit.substr(0, pos);
        toSplit.erase(0, pos + delimiter.length());
        data.push_back(token);
    }

    return data;
}


