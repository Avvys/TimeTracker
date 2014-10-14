/*
 * initializer.cpp
 *
 *  Created on: 14 paź 2014
 *      Author: abby
 */

#include "initializer.h"
#include "analyser.h"
#include "manager.h"

using namespace std;

const map<string, int> initializer::options = { { "-a", 1 }, { "-T", 0 } };

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
	cout << "Usage: " << endl;
	cout << "-a <file>  " << "print summary from file" << endl;
	cout << "-T         " << "start tracking" << endl;

	// TODO: cout << "-A <files>"<< endl;

}

void initializer::Run(const std::vector<std::string>& args) {
	_info(args.size());
	if (args.size() < 2) {
		PrintHelp();
		return;
	}

	runFlag = Parse(args);
	if (runFlag) {
		_fact("Parsing completed without error");
		Run(args.at(1), SubVec(2, args));
	} else
		PrintHelp();

}

void initializer::Run(const std::string& opt,
		const std::vector<std::string>& params) {

	const auto advOpt = options.find(opt);
	assert(advOpt != options.end()); // parser should check this

	if (opt == "-a") {
		analyser A(params.at(0));
	} else if (opt == "-T") {
		manager M;
	}

}

bool initializer::Parse(const std::vector<std::string>& args) {
	const auto opt = args.at(1);
	const auto it = options.find(opt);

	auto error = []() ->void {_erro("Invalid usage of this option");};

	if (it == options.end()) {
		_erro("Option " << opt << " does not exist");
		return false;
	}

	_dbg2("Found option: " << it->first << " -> " << it->second);
	const int numbP = it->second;
	const int bsize = args.size() - 2;

	_dbg2("bsize: " << bsize << " vs parm: " << numbP);

	// calculate numbers of next params

	if (bsize >= 0) {  // finite numbers of params
		if (numbP == bsize)
			_fact("all ok");
		else if (numbP < bsize)
			_warn("to many params for this options, last ones will be ignored");
		else if (numbP > bsize) {
			error();
			return false;
		}
	} else { // infinite params
		if (bsize < 1) { // no params = error
			error();
			return false;
		}
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
