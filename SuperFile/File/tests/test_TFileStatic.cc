#include "../TFile.h"

int testStatic() {
	TFile::copyFile("E:\\mksSandbox-0.log", "E:\\copy.txt");

	return 0;
}


int main() {
	std::cout << "Hello TFile_Static_test.cc!" << std::endl;
	testStatic();

	return 0;
}
