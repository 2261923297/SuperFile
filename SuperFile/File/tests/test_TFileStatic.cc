#include "../TFile.h"
#include "../TWinFile.h"

int test_getParent() {
	TFile::ptr tf = TFile::ptr(new TWinFile("C:\\abc\\123\\dfg\\"));

	std::cout << tf->getParent() << std::endl;

	std::cout << tf->getParent("D:\\abc\\123\\dfg\\") << std::endl;
	return 0;
}

int test_getParent2() {
	TFile::ptr tf = TFile::ptr(new TWinFile("C:\\abc\\123\\dfg"));

	std::cout << tf->getParent() << std::endl;

	std::cout << tf->getParent("D:\\abc\\123\\dfg") << std::endl;
	return 0;
}

int testStatic() {
	TFile::copyFile("E:\\mksSandbox-0.log", "E:\\copy.txt");

	return 0;
}


int main() {
	std::cout << "Hello TFile_Static_test.cc!" << std::endl;
//	testStatic();
	test_getParent();
	test_getParent2();
	return 0;
}
