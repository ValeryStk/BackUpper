#ifndef FILECOPIER_H
#define FILECOPIER_H
#include <string>
#include <atomic>
#include <future>
#include <vector>
#include <mutex>
#include <filesystem>
#include <iostream>
#include <tuple>
#include <chrono>
#include <iostream>
#include <fstream>

using std::atomic;
using std::string;
using std::cout;
using std::vector;
using std::pair;
using std::mutex;



class FileCopier{
public:
    FileCopier(std::string sourceDir,std::string backupDir);
    void startCopy();
    std::string makeOutFilePath(const string &inPath);

private:
    string   m_inDir;
    string   m_outDir;
    uint16_t m_threadsCount = 1;
    mutex    m_copyFinishMutex;
    atomic <uint64_t> m_completedFilesCounter = -1;
    atomic <uint64_t> m_copiedCounter;
    atomic <uint64_t> m_TotalSize;
    vector <pair<string,string>> m_paths;
    string getCurrentTimeStamp();

    void makeBackupNames();

};


#endif // FILECOPIER_H
