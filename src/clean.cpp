#include "clean.hpp"
#include "CompileCommands.hpp"

#include <map>
#include <regex>
#include <utility>

using namespace std;
using namespace filesystem;

static constexpr char PARAMETER_REGEX[] = R"([/-][-|/\w\\:\.~=\-\+]*)";

static const string EMPTY;

static const vector<pair<string_view, string>> PARTIAL_REPLACEMENTS = {
    { "/wd", EMPTY },
	{ "/Fo", EMPTY },
	{ "/FI", EMPTY },
    { "/D", "-D" }
};

static const map<string_view, string> FULL_REPLACEMENTS = {
    { "/TP", EMPTY },
    { "/GR", EMPTY },
	{ "/FS", EMPTY },
    { "/EHsc", EMPTY },
    { "/Zi", EMPTY },
    { "/Ob0", EMPTY },
    { "/Od", EMPTY },
    { "/RTC1", EMPTY },
    { "/nologo", EMPTY },
    { "/permissive-", EMPTY },
    { "/Zc:strictStrings-", EMPTY },
	{ "/FdTARGET_COMPILE_PDB", EMPTY },
    
    { "/Wall", "-Wall" }
};

bool cleanCompileCommands(const vector<string> &parameters)
{
    string inputFileName, outputFileName;

    if (parameters.size() == 0) {
        inputFileName = outputFileName = "compile_commands.json";
    } else if (parameters.size() == 1) {
		outputFileName = inputFileName;
    } else if (parameters.size() >= 2) {
		inputFileName = parameters.at(0);
		outputFileName = parameters.at(1);
    }
	return cleanCompileCommands(inputFileName, outputFileName);
}


bool cleanCompileCommands(const path &inputFileName, const path &outputFileName)
{
	CompileCommands compileCommands;
	compileCommands.read(inputFileName);

    for (CompileCommand &command : compileCommands) {
        command.command = cleanCommandParameters(command.command);
    }
	compileCommands.write(outputFileName);

	return false;
}

string cleanCommandParameters(const string &command)
{
    string cleanCommand;

    regex parameterRegEx(PARAMETER_REGEX);
    sregex_token_iterator parameterIter(command.begin(), command.end(), parameterRegEx, {-1, 0});
    sregex_token_iterator parameterEnd;

    for ( ;parameterIter != parameterEnd; ++parameterIter) {
        string parameter = *parameterIter;
        for (const auto &partialReplacement : PARTIAL_REPLACEMENTS) {
            if (parameter.starts_with(partialReplacement.first)) {
                if (string_view replacement = partialReplacement.second; replacement.empty())
                    parameter = replacement;
                else
                    parameter.replace(0, replacement.length(), replacement);
            }
        }
        if (auto replaceTextIter = FULL_REPLACEMENTS.find(parameter); replaceTextIter != FULL_REPLACEMENTS.end()) {
            string replacement = replaceTextIter->second;
            parameter = replacement;
        }
        cleanCommand += parameter;
    }
    return cleanCommand;
}
