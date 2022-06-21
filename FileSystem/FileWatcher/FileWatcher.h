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
#include "FileStates.h"

namespace fs = std::filesystem;
using std::string;
using std::cout;
using std::chrono::milliseconds;
using std::vector;
using std::pair;
using std::mutex;


class FileWatcher
{
public:
    FileWatcher(string inDir, string outDir);
    void checkFileTree();

private:
    string m_watchDir;
    string m_backupDir;
    std::unordered_map<string, fs::file_time_type> m_paths;
    vector <pair<string,FileStates>> m_files_states;

};

#endif // FILEWATCHER_H
