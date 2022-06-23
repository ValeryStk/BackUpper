#ifndef FILENAMEUTIL_H
#define FILENAMEUTIL_H
#include "string"

using std::string;

struct fileInfo{

    string path;
    string fileName;
    string dateTime;
    uint32_t version;

};


class FileNameUtil{
public:
    static string makeBackUpName(const string &inPath, const string &outDir, const uint32_t &version);
    static string getCurrentTimeStamp();
    static fileInfo getOriginPathFromBackupName(const string &backupName);
private:
    FileNameUtil() = delete;
   ~FileNameUtil() = delete;

};




#endif //FILENAMEUTIL_H
