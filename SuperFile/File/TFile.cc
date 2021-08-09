#include "TFile.h"



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

