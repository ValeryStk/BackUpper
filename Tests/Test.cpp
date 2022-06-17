#include "Core/Controller.h"
#include "Core/Configurator/Configurator.h"
#include "gtest/gtest.h"
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
	return RUN_ALL_TESTS();
	return 0;
}
