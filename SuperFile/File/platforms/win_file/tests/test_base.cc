#include <iostream>
#include "../WinFile.h"

int test_black() {
	WinFile wFile;
	std::string pathStr = "C:\\SoftWare\\Project\\cpp\\code\\*.*";
	WinFile::FileData_t fdata = WinFile::GetFileData(pathStr);

	return 0;
}

int main() {
	test_black();

	return 0;

}
