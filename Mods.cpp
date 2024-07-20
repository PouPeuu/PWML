#include "Mods.h"

std::vector<Mod> Mods::mods = {};

void Mods::load_from_folder(std::filesystem::path path) {
    std::vector<std::filesystem::path> paths = Utils::list_files(path);
    for (std::filesystem::path path : paths) {
        Mods::mods.push_back(Mod(path));
    }
}

void Mods::set_mod_active(uint index, bool active = true) {
    Mods::mods[index].set_active(active);
}

bool Mods::is_mod_active(uint index) {
    return Mods::mods[index].is_active();
}

Mod Mods::get_mod(uint index) {
    return Mods::mods[index];
}

std::vector<std::string> dirs = {
    "graphics",
    "levels",
    "music",
    "objects",
    "sound",
    "weapons"
};

void Mods::apply_mods() {
    for (std::string directory : dirs) {
        if (std::filesystem::exists(directory)) {
            std::filesystem::remove_all(directory);
        }
        std::filesystem::create_directory(directory);

        
    }
}