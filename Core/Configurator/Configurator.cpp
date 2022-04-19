#include "Configurator.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <memory>
#include "json.hpp"

using json = nlohmann::json;

struct Config {
    std::string rootDir;
    std::vector<std::string> backupDirs;
    std::string ip;
    int port = 0;
} tstr;



Configurator::Configurator()
{

}

void Configurator::parseConfigFile(const char* filename)
{

    auto f = std::make_unique<std::ifstream>(std::ifstream(filename));
    auto j = std::make_unique <json>(json());
    try {
        *j = json::parse(*f);
    }
    catch (json::parse_error err) {
        std::cout << "Json parsing error: " << err.what();
        return;
    }

    Config cfg;
    std::vector<std::string> backUpPathes;
    j->at("BackUpDirs").get_to(backUpPathes);
    j->at("DataBase").at("ip").get_to(cfg.ip);
    j->at("DataBase").at("port").get_to(cfg.port);

    for (auto& bp : backUpPathes) std::cout << bp << "\n";
    std::cout << cfg.ip << "\n";
    std::cout << cfg.port << "\n";
}
