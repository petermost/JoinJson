#include <vector>
#include <string>
#include <algorithm>
#include <pera_software/aidkit/vectors.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
using namespace pera_software::aidkit;
using namespace boost::property_tree;

int main( int argc, char *argv[] ) {
	vector<string> fileNames(&argv[0], &argv[argc]);
	vectors::pop_front(&fileNames);

	ptree allCompileCommands;
	for (const string &fileName : fileNames) {
		ptree compileCommands;
		read_json(fileName, compileCommands);
		allCompileCommands.insert(allCompileCommands.begin(), compileCommands.begin(), compileCommands.end());
	}
	write_json("compile_commands.json", allCompileCommands);
	return 0;
}
