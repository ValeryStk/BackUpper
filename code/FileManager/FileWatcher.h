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
    FileWatcher(string inDir, string outDir, std::chrono::duration<int, std::milli> delay) : m_watchDir{inDir},
        m_outDir{outDir},
        m_delay {delay}
    {

    }

    void start() {

        std::atomic <bool> isWatching = true;
        auto keyScanner = [&isWatching]() {
            while(true){
                std::this_thread::sleep_for(milliseconds(200));
                int keyCode = std::cin.get();
                if(keyCode=='q'){

                    cout<<"\nExiting from watch mode, please wait....\n";
                    isWatching.store(false);break;

                }else if(keyCode=='c'){

                    if (system("clear")) system( "cls" );
                }
                else if(keyCode=='h'){

                    cout<<"Press q to quit from watch mode\n\n";
                }
            };
        };
        std::thread threadScanner(keyScanner);


        auto doFileTasks = [&isWatching, this](){
            while(isWatching){

                m_pathsMutex.lock();
                if(m_copyTasks.empty()){
                    m_pathsMutex.unlock();
                    std::this_thread::sleep_for(milliseconds(1000));
                    //cout<<"sleep: "<<std::this_thread::get_id()<<"\n";
                    continue;
                }

                string in = m_copyTasks.back().first;
                string out = m_copyTasks.back().second;
                m_copyTasks.pop_back();
                m_pathsMutex.unlock();
                try{
                    auto copyOptions = fs::copy_options::update_existing;
                    fs::copy(in, out, copyOptions);
                    cout<<out<<" is updated.\n";
                }catch(fs::filesystem_error& e){
                    cout<<e.what()<<"\n";
                }

            }
        };

        std::uint16_t threadsCount =  std::thread::hardware_concurrency() - 2;//One thread - refresh dirs, another - keyboard scanner
        if(threadsCount==0)threadsCount = 1;
        vector<std::thread> tasks;
        for(int i = 0; i < threadsCount; ++i)
        {
            tasks.push_back(std::thread(doFileTasks));

        }

        while(isWatching.load()) {
            refreshFileTree(m_paths);
        }

        for(int i = 0; i < threadsCount; ++i)
        {
            tasks[i].join();
        }

        threadScanner.join();
    }

private:
    string m_watchDir;
    string m_outDir;
    std::chrono::duration<int, std::milli> m_delay;
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

        std::this_thread::sleep_for(m_delay);

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
