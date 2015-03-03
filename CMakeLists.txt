cmake_minimum_required(VERSION 2.8.6)

#if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#        message(FATAL_ERROR "Please use GCC compiler with C++11 support")
#endif ()


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost 1.55 REQUIRED COMPONENTS system filesystem chrono date_time)
set(Boost_LIBRARIES "${Boost_LIBRARIES}")


find_library(X_LIBRARIES NAMES Xmu X11) 
find_library(OTHER_LIBRARIES NAMES ICE SM glib-2.0)  


#add_subdirectory(otshell_utils)
add_subdirectory(src)

# add_executable(TimeTracker ${TIMETRACKER})
# target_link_libraries(TimeTracker otshell_utils ${Boost_LIBRARIES} boost_chrono ICE Xmu glib-2.0 SM boost_filesystem boost_system X11 boost_date_time)
