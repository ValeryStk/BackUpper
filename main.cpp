#include <iostream>
#include "Core/Controller.h"


using std::cout;

int main(){
	
	cout<<("Entry point");
	Controller core;
	char i;
	bool isRun = true;
	cout<<("\nEnter 'q' to exit...");
	while (isRun) {
		std::cin >> i;
		if (i == 'q')isRun = false;
	}
	return 0;
	
}