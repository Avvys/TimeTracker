/*
 * info.h
 *
 *  Created on: 7 paź 2014
 *      Author: abby
 */

#ifndef INFO_H_
#define INFO_H_

#include "libs.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>
#include <X11/Xmu/WinUtil.h>
#include <glib.h>

#include <glib-2.0/glib/gmem.h>
class info {
public:
	info();
	virtual ~info();

	static std::string GetCurrWorkspace(); // uses wmctrl and awk
	static std::string GetCurrDesktop();
	static std::string GetCurrWin(); // FIXME: For some application (e.g xchat) c-string is NULL (works for e.g. chromium)
	static std::string Command(char *cmd); // executes bash command and return >>output<<

	static gchar *get_property(Display *disp, Window win, Atom xa_prop_type,
			gchar *prop_name, unsigned long *size);

	static void Cut(std::string &s);

private:
	static gchar * GetProperty(Display *disp, Window win, Atom xa_prop_type,
			gchar *prop_name, unsigned long *size);

};

#endif /* INFO_H_ */
