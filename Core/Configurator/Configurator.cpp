#include "Configurator.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <memory>
#include "json.hpp"

using json = nlohmann::json;
using std::string;
using std::vector;
using std::ifstream;
using std::cout;


struct Config {
    string rootDir;
    vector<string> backupDirs;
    string ip;
    int port = 0;
} tstr;



Configurator::Configurator()
{

}

void Configurator::parseConfigFile(const char* filename)
{

    auto f = make_unique<ifstream>(ifstream(filename));
    auto j = make_unique <json>(json());
    try {
        *j = json::parse(*f);
    }
    catch (json::parse_error err) {
        cout << "Json parsing error: " << err.what();
        return;
    }

    Config cfg;
    std::vector<string> backUpPathes;
    j->at("BackUpDirs").get_to(backUpPathes);
    j->at("DataBase").at("ip").get_to(cfg.ip);
    j->at("DataBase").at("port").get_to(cfg.port);

    for (auto& bp : backUpPathes) cout << bp << "\n";
    cout << cfg.ip << "\n";
    cout << cfg.port << "\n";
}
