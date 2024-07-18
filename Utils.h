#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

namespace Utils {
    std::string read_file(std::string filepath);
    std::vector<std::string> list_files(std::string filepath);
    std::string get_executable_dir();
}
#endif