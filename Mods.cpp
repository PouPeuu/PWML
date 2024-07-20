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