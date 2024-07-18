#include "Mod.h"

using json = nlohmann::json;

Mod::Mod(std::filesystem::path path) {
    this->modpath = path;

    std::filesystem::path metadata_path = path / "metadata.json";

    if (std::filesystem::exists(metadata_path)){
        json modjson = json::parse(Utils::read_file(metadata_path));
        this->name = modjson["name"];
        this->short_description = modjson["short_description"];
    }

    std::cout << "Path: " << this->modpath << "\nName: " << this->name << "\nShort Description: " << this->short_description << std::endl;
}