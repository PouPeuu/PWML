#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

namespace Utils {
    std::string read_file(std::filesystem::path filepath);
    std::vector<std::filesystem::path> list_files(std::filesystem::path filepath);
    std::filesystem::path get_executable_dir();
}
#endif