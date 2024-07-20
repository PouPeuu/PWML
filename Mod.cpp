#include "Mod.h"

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
    
    if (fs::exists(modpath / "levels")) {
        for (fs::path path : fs::directory_iterator(modpath / "levels")) {
            if (path.filename() != "received") {
                fs::copy(path, "levels");
            }
        }
    }

    if (fs::exists(modpath / "music")) {
        for (fs::path path : fs::directory_iterator(modpath / "music")) {
            if (path.filename() != "menu_music.txt") {
                fs::copy(path, "music");
            } else {
                if (fs::exists("music/menu_music.txt")) {
                    std::string result = Utils::read_file("music/menu_music.txt") + "\n" + Utils::read_file(path);
                    Utils::write_file("music/menu_music.txt", result);
                } else {
                    fs::copy(path, "music/menu_music.txt");
                }
            }
        }
    }

    if (fs::exists(modpath / "objects")) {
        for(fs::path path : fs::directory_iterator(modpath / "objects")) {
            fs::copy(path, "objects");
        }
    }

    if (fs::exists(modpath / "sound")) {
        for (fs::path path : fs::directory_iterator(modpath / "sound")) {
            if (path.filename() != "Sounds.xml") {
                fs::copy(path, "sound");
            } else {
                Utils::clone_xml(path, "sound/Sounds.xml", "sounds");
            }
        }
    }
    
    if (fs::exists(modpath / "weapons")) {
        for (fs::path path : fs::directory_iterator(modpath / "weapons")) {
            if (path.extension() == "") {
                fs::copy(path, "weapons" / path.filename(), std::filesystem::copy_options::recursive);
            } else if (path.filename() == "extra.json") {
                if (fs::exists("weapons/extra.json")) {
                    json to = json::parse(Utils::read_file("weapons/extra.json"));
                    auto toweapons = to["weapons"];
                    json from = json::parse(Utils::read_file(path));
                    auto fromweapons = from["weapons"];

                    for (auto j : fromweapons) {
                        bool contains = false;
                        for (auto k : toweapons) {
                            if (j["name"] == k["name"]) {
                                contains = true;
                                break;
                            }
                        }

                        if (contains)
                            continue;
                        
                        toweapons.push_back(j);
                    }

                    Utils::write_file("weapons/extra.json", toweapons.dump());
                } else {
                    fs::copy(path, "weapons/extra.json");
                }
            }
        }
    }
}