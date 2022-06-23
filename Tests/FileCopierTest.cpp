#include "Core/Controller.h"
#include "Core/Configurator/Configurator.h"
#include "FileSystem/FileManager.h"
#include "FileSystem/FileCopier/FileCopier.h"
#include "FileSystem/FileNameUtil/FileNameUtil.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>
#include <iostream>

using std::string;
namespace fs = std::filesystem;

const string testFileName = "testFileNameExample_";
const string testInFolderName = "/_!TestInFolder";
const string testOutFolderName =  "/_!TestOutFolder";
const uint16_t numberTestFiles = 100;

void makeFilesInCurrentFolder(uint16_t filesNumber);
uint16_t getNumberOfFilesInFolder(std::string pathFolder);

TEST(FileCopier, createTestFiles){

    makeFilesInCurrentFolder(numberTestFiles);
    string path = (fs::current_path()/testInFolderName).string();
    uint16_t numberFiles = getNumberOfFilesInFolder(path);
    EXPECT_EQ(numberTestFiles,numberFiles);
}

TEST(FileCopier, copyTest){

    string in = (fs::current_path()/testInFolderName).string();
    string out = (fs::current_path()/testOutFolderName).string();
    if(fs::exists(out))fs::remove_all(out);
    fs::create_directory(out);
    FileCopier fc(in,out,1);
    fc.startCopy();
    uint16_t numberFiles = getNumberOfFilesInFolder(out);
    EXPECT_EQ(numberTestFiles,numberFiles);
}

TEST(FileCopier, makeOutFilePath){

    const string inDir = "d:/_in";
    const string outDir = "d:/_out";
    FileCopier fc(inDir,outDir,1);
    string path = "d:/_in/test/test2/test3";
    string expectedResult = "d:/_out/d_intesttest2test3";
    cout<<FileNameUtil::makeBackUpName(path,outDir,1)<<"  ++++   "<<expectedResult;
    string clearedFileName = FileNameUtil::makeBackUpName(path,outDir,1).substr(0,expectedResult.length());
    
    EXPECT_EQ(clearedFileName,expectedResult);
}

TEST(FileNameUtil, restoreInfoFromBackupFileName){

    string bun = "D_!TestInFoldertestFileNameExample_1.txt_1-2-17_2022-5-22-21-15-11_1";
    auto fi = FileNameUtil::getOriginPathFromBackupName(bun);
    cout<<"version: "<<fi.version<<"\n";
    cout<<"dateTime: "<<fi.dateTime<<"\n";
    cout<<"path: "<<fi.path<<"\n";
}

int main(int argc, char* argv[]){

    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    char exit;
    std::cin >> exit;
    return 0;
}

void makeFilesInCurrentFolder(uint16_t filesNumber){

    fs::path testFolderPath = fs::current_path()/testInFolderName;
    cout<<"TestFolderName: "<<testFolderPath;
    bool isDirExists = fs::exists(testFolderPath);
    if(isDirExists) fs::remove_all(testFolderPath);
    fs::create_directory(testFolderPath);
    for(int i=0;i<filesNumber;++i){
        std::string fileName = testFileName + std::to_string(i + 1) + ".txt";
        std::ofstream file(testFolderPath/fileName);
        file <<"Test text";
    }

};

uint16_t getNumberOfFilesInFolder(string pathFolder){
    uint16_t fileCounter = 0;
    for(auto &file : fs::recursive_directory_iterator(pathFolder)) {

        if(!file.is_directory()){
            ++fileCounter;
        }
    }
    return fileCounter;
};


