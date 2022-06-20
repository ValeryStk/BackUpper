#include <iostream>
#include "Core/Controller.h"
#include "FileSystem/FileManager.h"


using std::cout;

int main(){
	
	cout<<("Entry point\n");
	Controller core;
    FileManager fileManager;
    char i;
    bool isRun = true;
    core.startTimeManager();
	cout<<("\nEnter 'q' to exit...");
    while (isRun) {
        std::cin >> i;
        if (i == 'q')isRun = false;
    }
	return 0;
	
}
