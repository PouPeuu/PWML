#include "Mods.h"

std::vector<Mod> Mods::mods = {};

void Mods::load_from_folder(fs::path path) {
    std::vector<fs::path> paths = Utils::list_files(path);
    for (fs::path path : paths) {
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

void Mods::apply_mods() {
    const std::vector<std::string> dirs = {
        "graphics",
        "levels",
        "music",
        "objects",
        "sound",
        "weapons"
    };
    
    for (std::string directory : dirs) {
        if (fs::exists(directory)) {
            fs::remove_all(directory);
        }
        fs::create_directory(directory);
    }

    for (Mod mod : Mods::mods) {
        if (mod.is_active())
            mod.apply_mod();
    }
}