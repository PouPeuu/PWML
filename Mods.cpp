#include "Mods.h"

std::vector<Mod> Mods::mods = {};

void Mods::load_from_folder(std::filesystem::path path) {
    std::vector<std::filesystem::path> paths = Utils::list_files(path);
    for (std::filesystem::path path : paths) {
        Mods::mods.push_back(Mod(path));
    }
}