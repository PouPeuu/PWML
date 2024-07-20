#ifndef MODS_H
#define MODS_H

#include "Mod.h"
#include "Utils.h"

namespace Mods {
    extern std::vector<Mod> mods;

    void load_from_folder(std::filesystem::path path);

    void apply_mods();

    void set_mod_active(uint index, bool active = true);
    bool is_mod_active(uint index);
}
#endif