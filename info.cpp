/*
 * info.cpp
 *
 *  Created on: 7 paź 2014
 *      Author: abby
 */

#include "info.h"

#include <locale.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>
#include <X11/Xmu/WinUtil.h>

#include <glib-2.0/glib.h>

#define MAX_PROPERTY_VALUE_LEN 4096

using namespace std;

info::info() {
	// TODO Auto-generated constructor stub

}

info::~info() {
	// TODO Auto-generated destructor stub
}

std::string info::GetCurrDesktop() {
	Display *disp;
	disp = XOpenDisplay(NULL);
	Window root = DefaultRootWindow(disp);

	// getting number of desktops
	auto *num_desktops = GetProperty(disp, root, XA_CARDINAL, "_NET_NUMBER_OF_DESKTOPS",NULL);
	_dbg3("num_desk: " << typeid(num_desktops).name());
	//if(num_desktops=="0") num_desktops = GetProperty(disp, root, XA_CARDINAL, "_WIN_WORKSPACE_COUNT",NULL);
//	else {
//		_erro("Cannot get number of desktops properties");
//		return "";
//	}

	// getting number of current desktop
	auto cur_desktops = GetProperty(disp, root, XA_CARDINAL, "_NET_CURRENT_DESKTOP",NULL);
//	if(!num_desktops) num_desktops = GetProperty(disp, root, XA_CARDINAL, "_WIN_WORKSPACE",NULL);
//	else {
//		_erro("Cannot get current desktop properties");
//		return "";
//	}

	// geting names of workspaces
	unsigned long desktop_list_size = 0;
	auto list = GetProperty(disp,root, XInternAtom(disp,"UTF8_STRING",false), "_NET_CURRENT_DESKTOP", &desktop_list_size);
	// not utf8
//	if(!list) list = GetProperty(disp, root, XA_STRING, "_WIN_WORKSPACE_NAMES", &desktop_list_size);
//	assert(list);

	_info("list: " << list);

	return "";
}

string info::GetCurrWorkspace() {
	auto w = Command("wmctrl -d | grep \"*\" | awk \'{print $10 }\'"); // TODO better way to get workspace name
	assert(w != "ERROR");
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
	}
	else
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
	s = v.at(0);
}

gchar * info::GetProperty(Display* disp, Window win, Atom xa_prop_type,
		gchar* prop_name, unsigned long * size) {
	Atom xa_prop_name;
	Atom xa_ret_type;
	int ret_format;
	unsigned long ret_nitems;
	unsigned long ret_bytes_after;
//	unsigned long tmp_size;
	unsigned char *ret_prop;


	xa_prop_name = XInternAtom(disp, prop_name, false);

	auto ok = XGetWindowProperty(disp, win, xa_prop_name, 0,
			MAX_PROPERTY_VALUE_LEN / 4, false,
			xa_prop_type, &xa_ret_type, &ret_format,
			&ret_nitems, &ret_bytes_after, &ret_prop);
	_dbg3("x get window property: " << ok);
	// TODO: assert with ok, but how?
	// assert(xa_ret_type == xa_prop_type);

	auto tmp_size = (ret_format / 8) * ret_nitems;
	if(ret_format==32) tmp_size *= sizeof(long)/4;

	//assert(tmp_size>0);
	_dbg2("tmp_size: " << tmp_size);

	const std::string ret(reinterpret_cast<char*>(ret_prop));

	gchar *gret = new gchar [ ret.size() ];

	g_malloc(tmp_size+1);

	_dbg2("ret: " << ret);
	_dbg2("ret_prop: " << ret_prop);
	_dbg2("gret: " << gret);

	return gret;
}
