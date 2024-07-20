#include "Mod.h"

using json = nlohmann::json;

Mod::Mod(std::filesystem::path path) {
    this->active = false;
    this->modpath = path;
    this->id = path.filename();
    std::cout << id << std::endl;

    std::filesystem::path metadata_path = path / "metadata.json";
    std::filesystem::path description_path = path / "description.pml";

    if (std::filesystem::exists(metadata_path)){
        json modjson = json::parse(Utils::read_file(metadata_path));
        this->name = modjson["name"];
        this->short_description = modjson["short_description"];
    }
    
    if (std::filesystem::exists(description_path)) {
        this->long_description = Utils::read_file(description_path);
    }

    //std::cout << "Path: " << this->modpath << "\nName: " << this->name << "\nShort Description: " << this->short_description << std::endl;
}

std::string Mod::get_id() {
    return this->id;
}

std::string Mod::get_name() {
    return this->name;
}

std::string Mod::get_short_description() {
    return this->short_description;
}

std::string Mod::get_long_description() {
    return this->long_description;
}

bool Mod::is_active() {
    return this->active;
}

void Mod::set_active(bool active = true) {
    this->active = active;
}

void Mod::apply_mod() {
    
}