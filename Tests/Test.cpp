#include "Core/Controller.h"
#include "Core/Configurator/Configurator.h"
#include "FileSystem/FileManager.h"
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

int main(int argc, char* argv[]){

	::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    char exit;
    std::cin >> exit;
	return 0;
}
