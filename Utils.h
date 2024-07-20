#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <tinyxml2.h>
#include <nlohmann/json.hpp>
#include <algorithm>

using json = nlohmann::json;

namespace xml = tinyxml2;

namespace fs = std::filesystem;

namespace Utils {
    std::string read_file(fs::path filepath);
    void write_file(fs::path filepath, std::string contents);
    std::vector<fs::path> list_files(fs::path filepath);
    fs::path get_executable_dir();
    void clone_xml(fs::path from, fs::path to, std::string root_name);

    template <typename T>
    bool vector_contains(std::vector<T> vector, T value) {
        return std::find(vector.begin(), vector.end(), value) != vector.end();
    }
}
#endif