#include "Utils.h"

std::string Utils::read_file(fs::path filepath) {
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

void Utils::write_file(fs::path filepath, std::string contents) {
    std::ofstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error opening file " << filepath << std::endl;
        return;
    }

    file << contents;
    file.close();
}

std::vector<fs::path> Utils::list_files(fs::path path) {
    std::vector<fs::path> paths;
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            paths.push_back(entry.path());
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return paths;
}

void Utils::clone_xml(fs::path from, fs::path to, std::string root_name) {
    if (!fs::exists(to)) {
        fs::copy(from, to);
        return;
    }
    xml::XMLDocument fromdoc;
    xml::XMLError fromresult = fromdoc.LoadFile(from.string().c_str());
    xml::XMLDocument todoc;
    xml::XMLError toresult = todoc.LoadFile(to.string().c_str());

    xml::XMLNode* fromroot = fromdoc.FirstChildElement(root_name.c_str());
    xml::XMLNode* toroot = todoc.FirstChildElement(root_name.c_str());

    xml::XMLElement* element = fromroot->FirstChildElement();
    while (element != nullptr) {
        toroot->InsertEndChild(element->DeepClone(&todoc));
        element = element->NextSiblingElement();
    }

    xml::XMLError result = todoc.SaveFile(to.string().c_str());
}



#if defined(_WIN32)
#include <windows.h>
#include <algorithm>

fs::path Utils::get_executable_dir() {
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string path(buffer);
    size_t pos = path.find_last_of("\\/");
    return path.substr(0, pos);
}

#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>

fs::path Utils::get_executable_dir() {
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        std::string path(buffer);
        size_t pos = path.find_last_of("/");
        return path.substr(0, pos);
    }
    return "";
}

#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <vector>

fs::path Utils::get_executable_dir() {
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);  // Get the size needed
    std::vector<char> buffer(size);
    if (_NSGetExecutablePath(buffer.data(), &size) == 0) {
        std::string path(buffer.begin(), buffer.end());
        size_t pos = path.find_last_of("/");
        return path.substr(0, pos);
    }
    return "";
}

#else
#error "Unsupported platform"
#endif
