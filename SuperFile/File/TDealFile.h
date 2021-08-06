#pragma once
#include "TFile.h"



class TDealFile {
public:
	TDealFile(const std::string& filePath);

	int create();

	virtual ~TDealFile() { }

	int writeData(const char* fileCar, int carSize)
	
	std::string getParent();
	
	int readData(char* fileCar, int carSize, );
protected:
	TFile::ptr m_tFile;
	std::string m_filePath;
};

std::string TDealFile::getParent() {
	if(m_tFile.size() == 3) {
		std::cout << m_filePath << " is root dir" << std::endl;
	}
	if(m_tFile.size() < 3
		|| m_tFile[m_tFile.size() - 1] == '\\') {
		std::cout << m_filePath << " is err formate" << std::endl;
	}
	
	size_t pos = m_filePath.find_last_of('\\');
	return m_filePath.substr(pos);

}

int TDealFile::create() {

}


