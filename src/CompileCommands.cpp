#include "CompileCommands.hpp"
#include <boost/json.hpp>

using namespace std;
using namespace filesystem;
using namespace pera_software::aidkit::io;

namespace json = boost::json;

static const json::string_view DIRECTORY_KEY("directory");
static const json::string_view COMMAND_KEY("command");
static const json::string_view FILE_KEY("file");

size_t CompileCommands::read(const path &inputFileName)
{
    file inputFile(inputFileName, file::open_mode::read);

    return read(&inputFile);
}

size_t CompileCommands::read(file *inputFile)
{
    size_t count;
    char buffer[4096];
    string json;
	error_code errorCode;
	
    while ((count = inputFile->read(buffer, 1, sizeof(buffer), &errorCode)) > 0) {
        json.append(buffer, count);
    }
    return read(json);
}

size_t CompileCommands::read(const string &json)
{
    json::array array = json::parse(json).as_array();
    if (!array.empty()) {
        for (json::value &value : array) {
            json::object object = value.as_object();
            CompileCommand command = {
                .command = object[COMMAND_KEY].as_string().c_str(),
                .file = object[FILE_KEY].as_string().c_str(),
                .directory = object[DIRECTORY_KEY].as_string().c_str()
            };
            this->push_back(command);
        }
    }
    return array.size();
}

size_t CompileCommands::write(const path &outputFileName) const
{
    file outputFile(outputFileName, file::open_mode::write);

    return write(&outputFile);
}

size_t CompileCommands::write(file *outputFile) const
{
    string json;
    size_t count = write(&json);

    outputFile->write(json.data(), json.size(), 1);

    return count;
}

size_t CompileCommands::write(string *json) const
{
    json::array array;

    for (const auto &value : *this) {
        json::object object({
            { DIRECTORY_KEY, value.directory.string() },
            { COMMAND_KEY, value.command },
            { FILE_KEY, value.file.string() }
        });
        array.push_back(object);
    }
    *json = json::serialize(json::value(array));

    return array.size();
}


