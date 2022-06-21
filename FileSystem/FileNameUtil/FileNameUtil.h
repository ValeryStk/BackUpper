#ifndef FILENAMEUTIL_H
#define FILENAMEUTIL_H
#include "string"

using std::string;

class FileNameUtil{
public:
    static string makeBackUpName(const string &inPath, const string &outDir);
    static string getCurrentTimeStamp();
    static string getOriginPathFromBackupName(const string &backupName);
private:
    FileNameUtil() = delete;
   ~FileNameUtil() = delete;

};




#endif //FILENAMEUTIL_H
