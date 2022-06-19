#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <string>
#include <functional>
#include <stdlib.h>
#include <atomic>
#include <mutex>

namespace fs = std::filesystem;
using std::string;
using std::cout;
using std::chrono::milliseconds;
using std::vector;
using std::tuple;
using std::pair;
using std::mutex;


class FileWatcher
{
public:
    FileWatcher(string inDir, string outDir);


private:
    string m_watchDir;
    string m_outDir;
    std::unordered_map<string, fs::file_time_type> m_paths;
    vector <pair<string,string>> m_copyTasks;
    std::mutex m_pathsMutex;

    bool contains(const string &key) {
        auto el = m_paths.find(key);
        return el != m_paths.end();
    }

    void refreshFileTree(std::unordered_map<string, fs::file_time_type> &paths){


        if(!paths.empty())paths.clear();
        for(auto &file : fs::recursive_directory_iterator(m_watchDir)) {
            paths[file.path().string()] = fs::last_write_time(file);
            string inPath = file.path().string();
            string outPath = inPath;
            outPath.replace(0,m_watchDir.size(),m_outDir);
            if(fs::is_directory(file.status())){//Check if output directory exists
                if(!fs::exists(outPath)){
                    try{
                        fs::create_directory(outPath);
                        cout<<outPath + " -> folder is created\n";
                    }catch(fs::filesystem_error &e){
                        cout<<e.what();
                    }

                }
            }else if(fs::is_regular_file(file.status())){//Check if file in output directory exists

                if(!fs::exists(outPath)||fs::last_write_time(inPath)!=fs::last_write_time(outPath)){
                    try{

                        m_copyTasks.push_back(std::make_pair(inPath,outPath));

                    }catch(fs::filesystem_error &e){
                        cout<<e.what();
                    }

                }
            }

        }


        auto it = m_paths.begin();
        while (it != m_paths.end()) {
            if (!fs::exists(it->first)) {

                string outPath = it->first;
                outPath.replace(0,m_watchDir.size(),m_outDir);

                if(fs::is_directory(outPath)){
                    try{
                        fs::remove_all(outPath);
                        std::cout<<it->first<<" directory is deleted.\n";
                    }catch(fs::filesystem_error& e){
                        cout<<e.what()<<"\n";
                    }

                }else{
                    try{
                        fs::remove(outPath);
                        std::cout<<it->first<<" file is deleted.\n";
                    }catch(fs::filesystem_error& e){
                        cout<<e.what()<<"\n";
                    }
                }
                it = m_paths.erase(it);

            }
            else {
                it++;
            }
        }
    }


};

#endif // FILEWATCHER_H
