#ifndef MODS_H
#define MODS_H

#include "Mod.h"
#include "Utils.h"

namespace Mods {
    extern std::vector<Mod> mods;

    void load_from_folder(std::filesystem::path path);
}
#endif