#include "join.hpp"
#include "CompileCommands.hpp"
#include <iostream>

// TODO: Make it more robust against wrong command line parameters
// TODO: Move appendArray(), appendMap() to AidKit?

using namespace std;
using namespace filesystem;

bool joinCompileCommands(const vector<string> &parameters)
{
	vector<path> inputFileNames(parameters.begin(), parameters.end() - 2);
	path outputFileName(*(parameters.end() - 1));

	return joinCompileCommands(inputFileNames, outputFileName);
}

bool joinCompileCommands(const vector<path> &inputFileNames, const path &outputFileName)
{
	size_t count;
	CompileCommands compileCommands;

	for (const path &inputFileName : inputFileNames) {
		cout << "Reading file '" << inputFileName << "' ..." << endl;
		count = compileCommands.read(inputFileName);
		if (count > 0) {
			cout << "File '" << inputFileName << "' read " << count << " entries." << endl;
		} else {
			cerr << "File '" << inputFileName << "' could not be open for reading!" << endl;
		}
	}
	cout << "Writing file '" << outputFileName << "' ..." << endl;
	count = compileCommands.write(outputFileName);
	if (count > 0) {
		cout << "File '" << outputFileName << "' written " << count << " entries." << endl;
	} else {
		cerr << "File '" << outputFileName << "' could not be open for writing!" << endl;
	}
	return count > 0;
}

