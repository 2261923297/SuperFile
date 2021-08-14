#ifndef TFILE_H
#define TFILE_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <memory>
#include <direct.h>
#include <stdint.h>


class TFile {
public:
	typedef std::shared_ptr<TFile> ptr;
	TFile(std::string filePath) : m_path(filePath) {

	}
	virtual ~TFile() {

	}
	
	virtual uint64_t getFileSize() = 0;

	virtual int isExit() = 0;

	virtual int isDir() = 0;

	virtual int createFile(const char* path) = 0;

	virtual int createDir(const char* path) = 0;

	virtual std::vector<std::string> getNamesUnderDir() = 0;

	
	//end must '/'
	virtual int formateDirName(std::string& dirPath) = 0;

	virtual std::string getParent(const std::string& fileName = "") = 0;

	static int readData(char* buffer, int size, FILE* file);

	static int writeData(char* buffer, int size, FILE* file);

	static int copyFile(const char* fromPath, const char* toPath);

	
protected:
	std::string		m_path;
};
#endif //TFILE_H
