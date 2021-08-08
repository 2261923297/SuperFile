#ifndef TFILE_H
#define TFILE_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <memory>
#include <direct.h>
#include "platforms/win_file/WinFile.h"



class TFile {
public:
	typedef std::shared_ptr<TFile> ptr;
	TFile(std::string filePath) : m_path(filePath) {

	}
	virtual ~TFile() {

	}

	virtual int isExit() = 0;

	virtual int isDir() = 0;

	virtual int createFile(const char* path) = 0;

	virtual int createDir(const char* path) = 0;

	virtual std::vector<std::string> getNamesUnderDir() = 0;
	
	//end must '/'
	virtual int formateDirName(std::string& dirPath) = 0;

	static int readData(char* buffer, int size, FILE* file);

	static int writeData(char* buffer, int size, FILE* file);

	static int copyFile(const char* fromPath, const char* toPath);
protected:
	std::string		m_path;
};

int TFile::readData(char* buffer, int size, FILE* file) {
	if(nullptr == buffer) {
		return -1;
	}

	int nRead = fread(buffer, 1, size, file);
	if(-1 == nRead) {
		perror("TFile::readData");

	}
	return nRead;
}

int TFile::writeData(char* buffer, int size, FILE* file) {
	if(nullptr == buffer) {
		return -1;
	}

	int nWrite = fwrite(buffer, 1, size, file);

	if(-1 == nWrite) {
		perror("TFile::writeData");
	}

	return nWrite;
}

int TFile::copyFile(const char* fromPath, const char* toPath) {
	int copySize = 0, nRW = 0;
	int carSize = 1024;

	char fileCar[1025] = { 0 };
	FILE* pFromFile = fopen(fromPath, "rb+");
	FILE* pToFile = fopen(toPath, "ab+");
	if(!(pFromFile && pToFile)) {
		perror("copyFile_fopen");
		std::cout << "TFile::copyFile from: " << fromPath << " to: " << toPath << "; isCan^t open" << std::endl;
	}
	fseek(pFromFile, 0, SEEK_SET);
	fseek(pToFile, 0, SEEK_SET);

	int nRead = 0, nWrite = 0;
	do {
		nRead = readData(fileCar, carSize, pFromFile);
		if(nRead == -1) {
			return -1;
		}
		fileCar[nRead] = '\0';
		
		nWrite = writeData(fileCar, nRead, pToFile);
		if(nWrite != nRead || nWrite == -1) {
			return -1;
		}
		nRW++;
	} while(nRead == carSize);

	copySize = (nRW - 1) * carSize + nRead;
	return copySize;
}
#endif //TFILE_H
