#include "FileNameUtil.h"
#include <ctime>
#include "vector"
using std::vector;
using std::string;

string FileNameUtil::makeBackUpName(const string &inPath, const string &outDir, const uint32_t &version){

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
    string versionStr = "_";
    versionStr.append(std::to_string(version));
    string result = outDir + "/" + trimmedString + pathSignsPositions + getCurrentTimeStamp() + versionStr;
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
    return timeStamp;
}

fileInfo FileNameUtil::getOriginPathFromBackupName(const string &backupName)
{
    const int split_slashes = 3;
    fileInfo result;
    int slashCounter = 0;
    string slashesString = "";
    string pathWithoutSlashes = "";

    vector<int> slashPos;
    for(int i = backupName.length()-1;i>=0;--i){
        if(backupName[i]=='_'){
            ++slashCounter;
            slashPos.push_back(i);
            if(slashCounter==1){
                string version = backupName.substr(i+1,backupName.length()-i);
                result.version = std::stoi(version);

            }
            if(slashCounter==2)result.dateTime = backupName.substr(i+1, slashPos[0] - slashPos[1] - 1);
            if(slashCounter==3){
                slashesString = backupName.substr(i+1,slashPos[1]-slashPos[2] - 1);
                pathWithoutSlashes = backupName.substr(0,slashPos[2]);
            };
        }
        if(slashCounter == split_slashes)break;
    }


    std::string splitter = "-";

    size_t pos = 0;
    int position;
    vector<int> positions;
    while ((pos = slashesString.find(splitter)) != std::string::npos) {
        position = std::stoi(slashesString.substr(0, pos));
        positions.push_back(position);
        slashesString.erase(0, pos + splitter.length());
    }
    positions.push_back(std::stoi(slashesString));


    pathWithoutSlashes.insert(positions[0],":");
    for(int i=1;i<positions.size();++i){
        pathWithoutSlashes.insert(positions[i],"/");
    };

    result.path = pathWithoutSlashes;
    return result;
};
