file(GLOB_RECURSE TIMETRACKER *)

add_subdirectory(otshell_utils)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wl,--no-as-needed -pthread -std=c++11")
add_executable(TimeTracker ${TIMETRACKER})
target_link_libraries(TimeTracker otshell_utils ${Boost_LIBRARIES} boost_chrono ICE Xmu glib-2.0 SM boost_filesystem boost_system X11 boost_date_time  ${Boost_FILESYSTEM_LIBRARY}  ${Boost_SYSTEM_LIBRARY})

