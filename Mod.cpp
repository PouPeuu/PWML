#include "Mod.h"

using json = nlohmann::json;

Mod::Mod(fs::path path) {
    this->active = false;
    this->modpath = path;
    this->id = path.filename();
    fs::path metadata_path = path / "metadata.json";
    fs::path description_path = path / "description.pml";

    if (fs::exists(metadata_path)){
        json modjson = json::parse(Utils::read_file(metadata_path));
        this->name = modjson["name"];
        this->short_description = modjson["short_description"];
    }
    
    if (fs::exists(description_path)) {
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
    if (fs::exists(modpath / "graphics")) {
        for (fs::path path : fs::directory_iterator(modpath / "graphics")) {
            if (path.filename() != "Graphics.xml") {
                fs::copy(path, "graphics");
            } else {
                Utils::clone_xml(path, "graphics/Graphics.xml", "graphics");
            }
        }
    }
}