#include "join.hpp"
#include "clean.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <exception>

using namespace std;

int main(int argc, char *argv[])
{
	try {
		vector<string> arguments(&argv[0], &argv[argc]);
		if (arguments.size() == 1) {
			cerr << "Usage: " << arguments[0] << " join|merge|clean|cleanup <json_file_names>" << endl;
			return EXIT_FAILURE;
		}
		string command(arguments[1]);
		vector<string> parameters(arguments.begin() + 2, arguments.end());
		
		bool success = false;
		if (command == "join" || command == "merge") {
			success = joinCompileCommands(parameters);
		} else if (command == "clean" || command == "cleanup") {
			success = cleanCompileCommands(parameters);
		}
		return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
	} catch (const exception &exception) {
		cerr << "Exception: " << exception.what() << endl;
		return EXIT_FAILURE;
	}
}
