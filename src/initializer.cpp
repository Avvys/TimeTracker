/*
 * initializer.cpp
 *
 *  Created on: 14 paź 2014
 *      Author: abby
 */

#include "initializer.h"
#include "analyser.h"
#include "manager.h"
#include "timesheet.h"
#include "summary.h"
#include "test/detecttest.h"
using namespace std;

const map< string, pair_> initializer::options = {
		{ "-a",     {"<file> print timesheet from file",  "1"} },
		{ "-T",     {"start tracking" ,                   "0"} },
		{ "-Sd",    {"<files> print daily summary",      "-1"} },
		{ "-Sa",    {"<files> print all summary",        "-1"} },
		{ "-SS",    {"<files> save summary to file ",    "-1"} },
		{ "--help", {"print help" ,                       "0"} },
		{ "--test", {"run tests",                         "0"} }
};

initializer::initializer() :
		runFlag(false) {
	using namespace boost::posix_time;
	using namespace std;

	time_facet* facet(new time_facet("%Y-%m-%d"));
	cout.imbue(locale(cout.getloc(), facet));
}

initializer::~initializer() {
	// TODO Auto-generated destructor stub
}

void initializer::PrintHelp() {

	// TODO: cout << "-A <files>"<< endl;
	auto sep = "--------------------------------------------";
	cout << sep << endl;
	for(auto it : options) {
		cout << it.first << "\t " << it.second.front() << endl;
	}
	cout << sep << endl;

}

void initializer::Run(const std::vector<std::string>& args) {
	_info(args.size());
	if (args.size() < 2) {
		PrintHelp();
		return;
	}

	runFlag = Parse(args);

	if (runFlag) {
		_fact("Parsing completed without errors");
		Run(args.at(1), SubVec(2, args));
	}
	else
		PrintHelp();

}

void initializer::Run(const std::string& opt, const std::vector<std::string>& params) {
	using namespace std;

	//const auto advOpt = options.find(opt);
	//assert(advOpt != options.end()); // parser should check this

	//if (opt == "-a") analyser A(params.at(0));
	if (opt == "-a") timesheet T(params.at(0));
	if (opt == "-T") manager M;
	if (opt == "-Sd") summary S(params, false, false);
	if (opt == "-Sa") summary S(params,true, false);
	if (opt == "-SS") summary S(params, false, true);
	if (opt == "--help") PrintHelp();
	if (opt == "--test") detect_test test;

}

bool initializer::Parse(const std::vector<std::string>& args) {
	const auto opt = args.at(1);
	auto it = options.find(opt);

//	auto error = []() ->void {_erro("Invalid usage of this option");};

	if (it == options.end()) {
		_erro("Option " << opt << " does not exist");
		return false;
	}

	_dbg2("Found option: [" << it->first << " -> " << it->second.at(1) << "]");
	const int numbP = stoi(  it->second.at(1) );
	const int bsize = args.size() - 2;

	_dbg2("bsize: " << bsize << " vs parm: " << numbP);

	// calculate numbers of next params


	if (bsize >= 0 && numbP > -1) {  // finite numbers of params
		if (numbP == bsize)
			_fact("all ok");
		else if (numbP < bsize)
			_warn("to many args for this options, last ones will be ignored");
		else if (numbP > bsize) {
			_erro("Exepected " << numbP << " params");
			return false;
		}
	}
	if (numbP == -1 && bsize < 1) { // infinite params
		_erro("Expected 1>= args!");
		return false;
	}

	return true;
}

std::vector<std::string> initializer::SubVec(const size_t from,
		const std::vector<std::string>& fVec) {

	vector<string> subV;

	copy(fVec.begin() + from, fVec.end(), back_inserter(subV));

	for (auto tmp : subV)
		_dbg3(tmp);

	return subV;
}
