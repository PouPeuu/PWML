#include "Utils.h"

std::string Utils::read_file(std::string filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << filepath << std::endl;
        return NULL;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string contents = buffer.str();
    file.close();
    return contents;
}

std::vector<std::string> Utils::list_files(std::string path) {
    std::vector<std::string> paths;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            paths.push_back(entry.path());
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return paths;
}



#if defined(_WIN32)
#include <windows.h>
#include <algorithm>

std::string Utils::get_executable_dir() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string path(buffer);
    size_t pos = path.find_last_of("\\/");
    return path.substr(0, pos);
}

#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>

std::string Utils::get_executable_dir() {
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        std::string path(buffer);
        size_t pos = path.find_last_of("/");
        return path.substr(0, pos);
    }
    return std::string();
}

#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <vector>

std::string Utils::get_executable_dir() {
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);  // Get the size needed
    std::vector<char> buffer(size);
    if (_NSGetExecutablePath(buffer.data(), &size) == 0) {
        std::string path(buffer.begin(), buffer.end());
        size_t pos = path.find_last_of("/");
        return path.substr(0, pos);
    }
    return std::string();
}

#else
#error "Unsupported platform"
#endif
