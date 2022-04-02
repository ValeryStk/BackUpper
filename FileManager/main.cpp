#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include "FileWatcher.h"
#include "FileCopier.h"
#include "ArgumentsValidator.h"
using std::cout;
using std::string;
using std::chrono::milliseconds;
namespace fs = std::filesystem;

void pauseBeforeExit()
{
    cout<<"\nExample for copy mode: c c:\\in c:\\out 5\nExample for watch mode: w c:\\in c:\\out 5000";
    std::this_thread::sleep_for(milliseconds(5000));
}

int main(int argc, char *argv[])
{
    setlocale( LC_ALL, ".ACP" );
    cout <<"########################################\n"
           "############  File manager  ############\n"
           "########################################\n\n";


    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
    std::vector<std::string> m_args(argc);
    for(int i=0;i<argc;++i)m_args[i] = argv[i];
    ArgumentsValidator av{m_args};
    switch (av.getAppParams().parsingResult) {
    case CLI_ParsingResult::MIN_ARGS_NUMBER_ERROR:cout <<"Check number of the arguments...";pauseBeforeExit();return EXIT_FAILURE;
        break;
    case CLI_ParsingResult::WRONG_MODE:cout <<"You can use only c or w for mode argument.";pauseBeforeExit();return EXIT_FAILURE;
        break;
    case CLI_ParsingResult::NO_IN_FOLDER:cout <<"Folder for input files doesn't exists.";pauseBeforeExit();return EXIT_FAILURE;
        break;
    case CLI_ParsingResult::NO_OUT_FOLDER:cout <<"Folder for output files doesn't exists.";pauseBeforeExit();return EXIT_FAILURE;
        break;
    case CLI_ParsingResult::ERROR_TIMER_WATCH:cout <<"You can use only positive number for timer argument.";pauseBeforeExit();return EXIT_FAILURE;
        break;
    case CLI_ParsingResult::ERROR_THREADS_NUMBER:cout <<"You can use only positive number for threads argument.";pauseBeforeExit();return EXIT_FAILURE;
        break;
    case CLI_ParsingResult::OK:cout <<"Users arguments are correct.\n";
        break;

    }

    cout<<"Mode: "<<av.getAppParams().strMode<<'\n';
    cout<<"Input  path:"<<av.getAppParams().inFolder<<'\n';
    cout<<"Output path:"<<av.getAppParams().outFolder<<'\n';

    // Watch mode
    if(av.getAppParams().mode == Modes::Watcher){
        cout<<"Watching timer interval:"<<av.getAppParams().delay<<" ms"<<"\n\n";
        FileWatcher fw{av.getAppParams().inFolder,av.getAppParams().outFolder, milliseconds(av.getAppParams().delay)};
        std::thread fwThr(&FileWatcher::start,&fw);
        fwThr.join();
        cout<<"Watching mode was stopped.";
    }

    // Copy mode
    if(av.getAppParams().mode == Modes::Copy){
        cout<<"Number of threads:"<<av.getAppParams().threadNumber<<"\n\n";
        FileCopier fc{av.getAppParams().inFolder,av.getAppParams().outFolder,av.getAppParams().threadNumber};
        fc.startCopy();
    }

    return EXIT_SUCCESS;
}


