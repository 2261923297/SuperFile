#include <iostream>
#include "../../TWinFile.h"

static std::string filePath = "C:\\SoftWare";
int test_construct() {
	TFile* tFile = new TWinFile(filePath.c_str());

	delete tFile;
	return 0;
}

int test_isDir() {
	TFile* tFile = new TWinFile(filePath.c_str());
	std::cout << "isDir result: " << tFile->isDir() << std::endl;
	delete tFile;
	return 0;
}

int test_isExit() {
	TWinFile tWinFile(filePath.c_str());
	std::cout << "test_isExitRest: " << tWinFile.isExit();

	return 0;
}

void test_createDir() {
	TWinFile tWinFile(filePath.c_str());
	std::string createDirPath = "C:\\TWinFileTestDir\\Dir1\\Dir1.1";
	std::cout << "test_createDirRest: " << tWinFile.createDir(createDirPath.c_str()) << std::endl;
	
	createDirPath += "\\file.cc";
	std::cout << "test_createFileRest: " << tWinFile.createFile(createDirPath.c_str()) << std::endl;
}

void test_getNamesUnderDir() {
	TWinFile tWinFile(filePath.c_str());
	std::vector<std::string> v_files = tWinFile.getNamesUnderDir();
	for(auto iter : v_files) {
		std::cout << iter << ", ";
	}
	std::cout << std::endl;
}
int main() {
	std::cout << "Hello, Test_Base!" << std::endl;
	//test_construct();
	//test_isDir();
	//test_isExit();
	//test_createDir();
	test_getNamesUnderDir();
	return 0;
}
