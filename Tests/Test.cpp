#include "Core/Controller.h"
#include "Core/Configurator/Configurator.h"
#include "FileSystem/FileManager.h"
#include "FileSystem/FileCopier/FileCopier.h"
#include "gtest/gtest.h"
using std::string;

TEST(Controller, launchCase) {
	
    bool result = true;
	EXPECT_EQ(result,true);

}

TEST(Configurator, parsingJson) {

    Configurator cfg;
    cfg.parseConfigFile("d:/test.json");

}

TEST(FileCopier, makeOutFilePath){

    FileCopier fc("d:/_My_FIAT","d:/_out");
    string path = "d:/_in/test/test2/test3";
    string expectedResult = "d:/_out/d_intesttest2test3";
    cout<<fc.makeOutFilePath(path)<<"  ++++   "<<expectedResult;
    string clearedFileName = fc.makeOutFilePath(path).substr(0,expectedResult.length());
    fc.startCopy();
    EXPECT_EQ(clearedFileName,expectedResult);
}

int main(int argc, char* argv[]){

	::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    char exit;
    std::cin >> exit;
	return 0;
}
