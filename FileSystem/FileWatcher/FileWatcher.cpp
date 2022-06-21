#include "FileWatcher.h"
#include <string>
#include <chrono>
using std::chrono::milliseconds;

FileWatcher::FileWatcher(string inDir, string outDir)
{
    m_watchDir  = inDir;
    m_backupDir = outDir;
}
void FileWatcher::checkFileTree()
{

    std::unordered_map<string,pair<string, fs::file_time_type>> watchDir;
    std::unordered_map<string,pair<string,fs::file_time_type>>  backUpDir;

    for(auto &file : fs::recursive_directory_iterator(m_watchDir)) {
        if(fs::is_regular_file(file.status())){
            string file_name = file.path().filename().string();
            watchDir[file_name] = pair<string, fs::file_time_type>(file.path().string(),fs::last_write_time(file));
        }
    }

    for(auto &file : fs::recursive_directory_iterator(m_backupDir)) {
        if(fs::is_regular_file(file.status())){
            string file_name = file.path().filename().string();
            backUpDir[file_name] = pair<string, fs::file_time_type>(file.path().string(),fs::last_write_time(file));

            if(!watchDir.count(file_name)){

                m_files_states.push_back(pair<string,FileStates>(file_name,FileStates::DELETED));
                continue;
            }

            if(watchDir[file_name].second != backUpDir[file_name].second){

                m_files_states.push_back(pair<string,FileStates>(file_name,FileStates::CHANGED));
                continue;
            }

        }
    }


}

//string inPath = file.path().string();
//string outPath = inPath;
//outPath.replace(0,m_watchDir.size(),m_backupDir);

//if(fs::is_regular_file(file.status())){

//    if(!fs::exists(outPath)){
//        try{

//            m_files_states.push_back(pair<string,FileStates>(inPath,FileStates::ADDED));

//        }catch(fs::filesystem_error &e){
//            cout<<e.what();
//        }

//    }

//    if(fs::last_write_time(inPath)!=fs::last_write_time(outPath)){

//        try{

//            m_files_states.push_back(pair<string,FileStates>(inPath,FileStates::CHANGED));

//        }catch(fs::filesystem_error &e){
//            cout<<e.what();
//        }

//    }

//}
