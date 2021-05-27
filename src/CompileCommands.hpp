#pragma once

#include <map>
#include <vector>
#include <filesystem>
#include <pera_software\aidkit\io\file.hpp>

struct CompileCommand {
    std::string command;
	std::filesystem::path file;
    std::filesystem::path directory;
};

class CompileCommands : public std::vector<CompileCommand> {
	public:
		size_t read(const std::filesystem::path &inputFileName);
		size_t read(pera_software::aidkit::io::file *inputFile);
        size_t read(const std::string &json);

		size_t write(const std::filesystem::path &outputFileName) const;
		size_t write(pera_software::aidkit::io::file *outputDevice) const;
        size_t write(std::string *json) const;
};
