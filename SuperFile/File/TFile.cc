#include <iostream>

#include "TFile.h"

TFile::TFile() {


}
TFile::~TFile() {};

int TFile::isExit(const char* path) {
	int ans = 0;


	return ans;
}

int TFile::isDir(const char* path) {
	int ans = 0;

	return ans;
}

int TFile::creadFile(const char* path, const char* fileName) {
	int ans = 0;

	return ans;
}

int TFile::creadDir(const char* path, const char* dirName) {
	int ans = 0;

	return ans;
}

std::vector<std::string> TFile::getNamesUnderDir(const char* dirPath) {
	std::vector<std::string> ans;


	return ans;
}
	
//end must '/'
int TFile::formatDirName(std::string& dirPath) {
	int ans = 0;
	if(dirPath.size() == 0) {
		ans = -1;
	}

	if(-1 != ans) {
		if(dirPath[dirPath.size() - 1] != DIR_SEPARATOR) {
			dirPath += DIR_SEPARATOR;
			ans = 1;
		}
	}

	return ans;
}

std::string TFile::formatDirName(const char* dirPath) {
	std::string str = dirPath;
	formatDirName(str);

	return str;
}


int main() {
	std::cout << "TFile coming!" << std::endl;


	return 0;
}
