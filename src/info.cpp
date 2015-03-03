/*
 * info.cpp
 *
 *  Created on: 7 paź 2014
 *      Author: abby
 */

#include "info.h"
#define MAXSTR 1000

using namespace std;

Display *info::display;
unsigned long info::window;
unsigned char *info::prop;

info::info() {
	// TODO Auto-generated constructor stub

}

info::~info() {
	// TODO Auto-generated destructor stub
}

string info::GetCurrWorkspace() {
	string cmd = " wmctrl -d | grep \"*\" | awk \'{print $10 }\' ";

//	char *c_cmd = cmd.c_str();


	auto workspace = Command(cmd); // TODO better way to get workspace name
	assert(workspace != "ERROR");
	workspace.pop_back(); // delete new line char
	return workspace;
}

std::string info::GetCurrWin() {
	Display *display1;
	Window focus;
	char *window_name;
	int revert;

	display1 = XOpenDisplay(NULL);
	XGetInputFocus(display1, &focus, &revert);
	XFetchName(display1, focus, &window_name);

	//cout << "tittle: " << window_name << endl;

	if (window_name) {
		const string win_name(window_name);
		return win_name;
	}
	else
		return "";
}

std::string info::Command(string cmd) {
	FILE* pipe = popen(cmd.c_str(), "r");
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

std::pair<std::string, std::string> info::GetCurrWindow() {
	char *display_name = NULL;  // could be the value of $DISPLAY
	//XCloseDisplay(display);

	display = XOpenDisplay(display_name);
	if (display == NULL) {
		_erro("unable to open display");
		return pair<string, string>("", "");
		//fprintf(stderr, "%s:  unable to open display '%s'\n", argv[0], XDisplayName(display_name));
	}
	int screen = XDefaultScreen(display);
	window = RootWindow(display, screen);
	window = get_long_property("_NET_ACTIVE_WINDOW");

//	printf("_NET_WM_PID: %lu\n", get_long_property("_NET_WM_PID"));
//	printf("WM_CLASS: %s\n", get_string_property("WM_CLASS"));
//	printf("_NET_WM_NAME: %s\n", get_string_property("_NET_WM_NAME"));




	const string classWin = nOT::nUtils::ToStr(get_string_property("WM_CLASS"));
	const string nameWin = nOT::nUtils::ToStr(get_string_property("_NET_WM_NAME"));

	assert(classWin != "");
	assert(nameWin != "");

	const pair<string, string> winInfo(nameWin, classWin);
	XCloseDisplay(display);

	return winInfo;
}

void info::Cut(std::string& s) {
	auto v = nOT::nUtils::SplitString(s);
	s = v.at(0);
}
vector<string> info::splitString(string toSplit, string delimiter) {
	assert(toSplit != "");
	assert(delimiter != "");

	if (nOT::nUtils::ToStr(toSplit.back()) != delimiter)
	toSplit += delimiter;

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

void info::check_status(int status, unsigned long window) {
	if (status == BadWindow) {
		printf("window id # 0x%lx does not exists!", window);
		exit(1);
	}

	if (status != Success) {
		printf("XGetWindowProperty failed!");
		exit(2);
	}
}

unsigned char* info::get_string_property(string property_name) {
	Atom actual_type, filter_atom;
	int actual_format, status;
	unsigned long nitems, bytes_after;

	filter_atom = XInternAtom(display, property_name.c_str(), True);
	status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
			&actual_type, &actual_format, &nitems, &bytes_after, &prop);
	check_status(status, window);
	return prop;

}

unsigned long info::get_long_property(string property_name) {
	get_string_property(property_name);
	unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);
	return long_property;

}
