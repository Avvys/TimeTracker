## Time Tracker 
Simple Time Tracker written in C++11 based on switching X11 workspaces,
logging time information to readable text files.
(mainly for linux etc - see Comments)

### Build  
In TimeTracker directory:
``` 
mkdir build/ && cd build/
cmake .. && make 
``` 

### Needed dependencies 
GCC (with C++11 support), Boost 1.55 

Libraries: boost_chrono ICE Xmu glib-2.0 SM boost_filesystem boost_system X11 boost_date_time 

### Other info 
Time Tracker gets X11 desktop name.
Will also use X11 window name.
Currently uses wmctrl with grep and awk to detect current workspace name.

### TODO
* parse in C++11, not with grep
* get deskto name with Xlib directly, not by calling wmctrl program
* get window name
* allow exaxt rules (in code)
* allow rules from simple text file

### Comments 
This is a beta version! Tested on Debian Wheezy and Gnome Classic only!

### Licence

OpenBSD licence.


