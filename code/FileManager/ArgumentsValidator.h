#ifndef ARGUMENTSVALIDATOR_H
#define ARGUMENTSVALIDATOR_H
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <filesystem>
using std::cout;
using std::string;
namespace fs = std::filesystem;

const int MIN_NUMBER_ARGS = 5;
enum class CLI_ParsingResult {MIN_ARGS_NUMBER_ERROR, WRONG_MODE, NO_IN_FOLDER, NO_OUT_FOLDER, ERROR_TIMER_WATCH, ERROR_THREADS_NUMBER, OK};
enum class Modes {Copy, Watcher};

struct AppParams{
    CLI_ParsingResult parsingResult;
    Modes mode;
    string strMode;
    string inFolder;
    string outFolder;
    uint16_t delay;
    uint16_t threadNumber;
};


class ArgumentsValidator{
public:
    ArgumentsValidator(std::vector<string> args):m_args{args}{

        if(m_args.size()<MIN_NUMBER_ARGS){
            m_appParams.parsingResult = CLI_ParsingResult::MIN_ARGS_NUMBER_ERROR;
            return;
        }
        if(m_args[1]!="c"&&m_args[1]!="w"){
            m_appParams.parsingResult = CLI_ParsingResult::WRONG_MODE;
            return;
        }else {
            if(m_args[1]=="c") {m_appParams.mode = Modes::Copy;m_appParams.strMode = "copy mode";}
            if(m_args[1]=="w") {m_appParams.mode = Modes::Watcher;m_appParams.strMode = "watch mode";}
        }
        if(!isDirExists(m_args[2])){m_appParams.parsingResult = CLI_ParsingResult::NO_IN_FOLDER;return;}
        m_appParams.inFolder =  m_args[2];

        if(!isDirExists(m_args[3])){m_appParams.parsingResult = CLI_ParsingResult::NO_OUT_FOLDER;return;}
        m_appParams.outFolder = m_args[3];

        unsigned int checkValue = std::stoi(m_args[4]);
        if(m_appParams.mode == Modes::Watcher){
            if(checkValue>10000){
             checkValue = 10000;
            //m_appParams.parsingResult = CLI_ParsingResult::ERROR_TIMER_WATCH;return;
            }else m_appParams.delay = checkValue;
        }

        if(m_appParams.mode == Modes::Copy){
            if(checkValue<0){
            m_appParams.parsingResult = CLI_ParsingResult::ERROR_THREADS_NUMBER;return;
            }else {
                if(checkValue <= std::thread::hardware_concurrency()){
                m_appParams.threadNumber = checkValue;
                }else{
                m_appParams.threadNumber =  std::thread::hardware_concurrency();
                std::cout<<"It is not effectively to use the number of threads more than number of CPU cores...\n";
                std::cout<<"Your threads number argument have been reduced to "<<std::thread::hardware_concurrency()<<"\n";
                }
            }
        }

        m_appParams.parsingResult = CLI_ParsingResult::OK;
    }
    AppParams getAppParams()const{
        return m_appParams;
    };

private:
    std::vector<std::string> m_args;
    struct AppParams m_appParams;

    bool isDirExists(string path)const{
        if (!fs::exists(path))return false;
        else return true;
    };

};
#endif // ARGUMENTSVALIDATOR_H
