#pragma once

#include <vector>
#include <string>
#include <filesystem>

bool joinCompileCommands(const std::vector<std::string> &parameters);
bool joinCompileCommands(const std::vector<std::filesystem::path> &inputFileNames, const std::filesystem::path &outputFileName);
