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
using std::thread;
using std::atomic;
using std::string;
using std::cout;
using std::vector;
using std::pair;
using std::mutex;
using std::ios;
using std::fstream;
using std::ostream;
namespace fs = std::filesystem;
using namespace std::chrono;


class FileCopier{
public:
    FileCopier(string inDir, string outDir, uint16_t threads):m_inDir{inDir},
                                                         m_outDir{outDir},
                                                         m_threadsCount {threads}{

     m_TotalSize = 0;
    }

    void startCopy(){

        makeDirs();
        const uint64_t numberOfFiles = m_paths.size();
        m_completedFilesCounter = -1;
        m_copiedCounter = 0;
        if(m_threadsCount > numberOfFiles)m_threadsCount = (uint16_t)numberOfFiles;
        cout<<"Total number of files to copy: "<<numberOfFiles<<"\n";
        cout<<"Total size for all files: "<<m_TotalSize/1024.0/1024.0<<" MByte\n";
        cout<<"Start copy process....\n";
        auto start = high_resolution_clock::now();
        m_TotalSize = 0;
        std::atomic <bool> isCopy = true;
        auto keyScanner = [&isCopy, this]() {
            while(true){
                std::this_thread::sleep_for(milliseconds(50));
                int keyCode = std::cin.get();
                if(keyCode=='q'){
                    cout<<"\nExiting from copy mode, please wait....\n";
                    isCopy.store(false);break;
                }else if(keyCode=='s'){

                   cout<<"Copied files: "<<m_copiedCounter<<"\n";
                   cout<<"Copied size: "<<m_TotalSize/1024.0/1024.0 <<" MByte\n";
                }
                else if(keyCode=='h'){

                    cout<<"Press q to quit from watch mode\n\n";
                }
            };
        };
        thread threadScanner(keyScanner);



        auto copyFiles = [&numberOfFiles, this, &isCopy](){
            while(isCopy){
                //m_copiedFilesMutex.lock();//Mutex is slower then atomic                
                uint64_t counter = ++m_completedFilesCounter;//atomic vs mutex
                //m_copiedFilesMutex.unlock();

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

private:
    string   m_inDir;
    string   m_outDir;
    uint16_t m_threadsCount = 1;
    mutex    m_copyFinishMutex;
    atomic <uint64_t> m_completedFilesCounter = -1;
    atomic <uint64_t> m_copiedCounter;
    atomic <uint64_t> m_TotalSize;
    vector<pair<string,string>> m_paths;

    void makeOutFilePath(string &path){
        path.replace(0,m_inDir.size(),m_outDir);
    };

    void makeDirs(){
        for(auto &file : fs::recursive_directory_iterator(m_inDir)) {

            string sourceFile = file.path().string();
            string copyFile = sourceFile;
            makeOutFilePath(copyFile);
            if(file.is_directory()){

                if(!fs::exists(copyFile)){
                    try{
                        fs::create_directory(copyFile);
                    }catch(fs::filesystem_error& e){
                        cout<<e.what();
                    }
                }
            }else{
                m_TotalSize += fs::file_size(sourceFile);
                m_paths.push_back(std::make_pair(sourceFile,copyFile));
            }
        }

    }

    void copyOneFile(const string &sourcePath, const string &destinationPath){
        const int BUF_SIZE = 1024*16;
        std::ifstream in(sourcePath,ios::in|ios::binary);
        std::ofstream out(destinationPath,ios::out|ios::binary);
        char buf[BUF_SIZE];
        do {
            in.read(&buf[0], BUF_SIZE);
            out.write(&buf[0], in.gcount());
        } while (in.gcount() > 0);
        in.close();
        out.close();
    }

};


#endif // FILECOPIER_H
