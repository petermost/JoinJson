#pragma once

#include <vector>
#include <string>
#include <filesystem>

bool cleanCompileCommands(const std::vector<std::string> &parameters);
bool cleanCompileCommands(const std::filesystem::path &inputFileName, const std::filesystem::path &outputFileName);
std::string cleanCommandParameters(const std::string &command);
