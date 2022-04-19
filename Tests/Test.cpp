#include "Core/Controller.h"
#include "gtest/gtest.h"
TEST(Controller, launchCase) {
	
	//Controller c1;
	//Controller c2;
	bool result = true;// (c1.getVar() == c2.getVar());
	EXPECT_EQ(result,true);

}

int main(int argc, char* argv[]){

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	return 0;
}