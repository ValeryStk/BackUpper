#include "FileCopier.h"
#include "FileNameUtil.h"
#include <ctime>
using std::thread;
using std::ios;
using std::fstream;
using std::ostream;

namespace fs = std::filesystem;
using namespace std::chrono;

FileCopier::FileCopier(string sourceDir, string backupDir)
{
    m_inDir = sourceDir;
    m_outDir = backupDir;
    m_threadsCount = thread::hardware_concurrency();
}

void FileCopier::startCopy(){

    vector<std::pair<string, string> > pathes;
    makeBackupNames();
    const uint64_t numberOfFiles = m_paths.size();
    m_completedFilesCounter = -1;
    m_copiedCounter = 0;
    if(m_threadsCount > numberOfFiles)m_threadsCount = (uint16_t)numberOfFiles;
    cout<<"Total number of cores: "<<m_threadsCount<<"\n";
    cout<<"Total number of files to copy: "<<numberOfFiles<<"\n";
    cout<<"Total size for all files: "<<m_TotalSize/1024.0/1024.0<<" MByte\n";
    cout<<"Start copy process....\n";
    auto start = high_resolution_clock::now();
    m_TotalSize = 0;
    std::atomic <bool> isCopy = true;

    auto copyFiles = [&numberOfFiles, this, &isCopy](){
        while(isCopy){

            uint64_t counter = ++m_completedFilesCounter;

            if( counter >= numberOfFiles){
                std::lock_guard<mutex> lock(m_copyFinishMutex);
                cout<<"Thread with id: "<<std::this_thread::get_id() <<" is finished.\n";
                break;
            }

            string inFile  = m_paths.at(counter).first;
            string outFile = m_paths.at(counter).second;
            try{
                const auto copyOptions = fs::copy_options::skip_existing;
                fs::copy_file(inFile,outFile,copyOptions);
                m_TotalSize += fs::file_size(inFile);
                ++m_copiedCounter;
            }catch(fs::filesystem_error& e){
                cout<<e.what();
            }
        }
    };

    vector<std::thread> tasks;
    for(int i = 0; i < m_threadsCount; ++i)
    {
        tasks.push_back(std::thread(copyFiles));
    }
    for(int i = 0; i < m_threadsCount; ++i)
    {
        tasks[i].join();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);

    uint64_t hour = duration.count() / 3600;
    uint64_t min = (duration.count() - hour * 3600) / 60;
    uint64_t sec  = duration.count() - hour * 3600 - min * 60;
    cout<<"\nTotal size of the copied files: "<<m_TotalSize/1024.0/1024.0<<" MByte\n";
    cout <<"Elapsed time: "<< hour << ":" << min << ":" <<sec <<"\n";
}


void FileCopier::makeBackupNames(){

    for(auto &file : fs::recursive_directory_iterator(m_inDir)) {

        if(!file.is_directory()){

            string sourceFile = file.path().string();
            string backUpFile = sourceFile;
            m_TotalSize += fs::file_size(sourceFile);
            string outFilePath = FileNameUtil::makeBackUpName(backUpFile,m_outDir);
            m_paths.push_back(std::make_pair(sourceFile, outFilePath));

        }
    }
}

