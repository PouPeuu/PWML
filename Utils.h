#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <tinyxml2.h>

namespace xml = tinyxml2;

namespace fs = std::filesystem;

namespace Utils {
    std::string read_file(fs::path filepath);
    std::vector<fs::path> list_files(fs::path filepath);
    fs::path get_executable_dir();
    void clone_xml(fs::path from, fs::path to, std::string root_name);
}
#endif