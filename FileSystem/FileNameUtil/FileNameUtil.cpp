#include "FileNameUtil.h"
#include <ctime>


string FileNameUtil::makeBackUpName(const string &inPath, const string &outDir){

    if(inPath.empty())return inPath;
    string pathSignsPositions = "_";
    string trimmedString = "";
    for(int i=0;i<inPath.size();++i){
        if(inPath[i] == '/' || inPath[i] == '\\' || inPath[i] == ':'){

            pathSignsPositions = pathSignsPositions + std::to_string(i)+"-";
        }else{

            trimmedString.append(1,inPath[i]);
        }
    }
    pathSignsPositions.pop_back();
    pathSignsPositions.append("_");
    string result = outDir + "/" + trimmedString + pathSignsPositions + getCurrentTimeStamp() + ".ens";
    return result;
};

string FileNameUtil::getCurrentTimeStamp()
{

    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime,&now);

    std::string timeStamp;
    timeStamp.append(std::to_string(1900 + newtime.tm_year));
    timeStamp.append("-");
    timeStamp.append(std::to_string(newtime.tm_mon));
    timeStamp.append("-");
    timeStamp.append(std::to_string(newtime.tm_mday));
    timeStamp.append("-");
    timeStamp.append(std::to_string(newtime.tm_hour));
    timeStamp.append("-");
    timeStamp.append(std::to_string(newtime.tm_min));
    timeStamp.append("-");
    timeStamp.append(std::to_string(newtime.tm_sec));
    return timeStamp;}

string FileNameUtil::getOriginPathFromBackupName(const string &backupName)
{
    string result;
    return result;
};
