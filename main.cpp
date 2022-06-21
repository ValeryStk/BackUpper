#include <iostream>
#include "Core/Controller.h"
#include "FileSystem/FileManager.h"
#include "FileSystem/FileWatcher/FileWatcher.h"


using std::cout;

int main(){
	

    char i;
	cout<<("\nEnter 'q' to exit...");
    while (1) {
        std::cin >> i;
        if (i == 'q')break;
    }
	return 0;
	
}
