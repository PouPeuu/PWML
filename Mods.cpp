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

    std::vector<std::string> misfit;
    std::vector<std::string> ship_weapons;
    std::vector<std::string> pilot_weapons;

    for (fs::path path : fs::directory_iterator("weapons")) {
        if (fs::exists(path / "metadata.json")) {
            json metadata = json::parse(Utils::read_file(path / "metadata.json"));
            std::string weapon_type = metadata["type"];

            if (weapon_type == "ship") {
                ship_weapons.push_back(path.filename());
            } else if (weapon_type == "pilot") {
                pilot_weapons.push_back(path.filename());
            } else if (weapon_type == "both") {
                ship_weapons.push_back(path.filename());
                pilot_weapons.push_back(path.filename());
            } else {
                misfit.push_back(path.filename());
            }
        }
    }

    if (fs::exists("weapons/extra.json")) {
        json j = json::parse(Utils::read_file("weapons/extra.json"));
        for (auto k : j["weapons"]) {
            if (k["type"] == "ship") {
                ship_weapons.push_back(k["name"]);
            } else if (k["type"] == "ship") {
                ship_weapons.push_back(k["name"]);
            } else if (k["type"] == "pilot") {
                pilot_weapons.push_back(k["name"]);
            } else if (k["type"] == "both"){
                ship_weapons.push_back(k["name"]);
                pilot_weapons.push_back(k["name"]);
            } else {
                misfit.push_back(k["name"]);
            }
        }
    }

    std::vector<std::string> all_weapons;

    for (std::string weapon : ship_weapons) {
        all_weapons.push_back(weapon);
    }

    for (std::string weapon : pilot_weapons) {
        if (!Utils::vector_contains(all_weapons, weapon)) {
            all_weapons.push_back(weapon);
        }
    }

    for (std::string weapon : misfit) {
        if (!Utils::vector_contains(all_weapons, weapon)) {
            all_weapons.push_back(weapon);
        }
    }

    std::sort(all_weapons.begin(), all_weapons.end());
    std::sort(pilot_weapons.begin(), pilot_weapons.end());
    std::sort(ship_weapons.begin(), ship_weapons.end());

    std::string weapons_file;
    weapons_file += "Weapons:\n";
    
    for (std::string weapon : all_weapons) {
        weapons_file += "  " + weapon + "\n";
    }

    weapons_file += "Ship weapons:\n";

    for (std::string weapon : ship_weapons) {
        weapons_file += "  " + weapon + "\n";
    }

    weapons_file += "Pilot weapons:\n";

    for (std::string weapon : pilot_weapons) {
        weapons_file += "  " + weapon + "\n";
    }

    Utils::write_file("weapons/Weapons.dat", weapons_file);
}