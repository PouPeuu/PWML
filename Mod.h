#ifndef MOD_H
#define MOD_H

#include "Utils.h"
#include <nlohmann/json.hpp>
#include <string>

class Mod {
    private:
        bool active;

        std::string id;
        std::filesystem::path modpath;
        std::string name;
        std::string short_description;
        std::string long_description;
    public:
        Mod(std::filesystem::path path);

        std::string get_id();
        std::string get_name();
        std::string get_short_description();
        std::string get_long_description();

        bool is_active();
        void set_active(bool active);

        void apply_mod();
};

#endif