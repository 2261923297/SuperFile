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

	virtual int isExit();

	virtual int isDir();

	virtual int createFile(const char* path);

	virtual int createDir(const char* path);

	virtual std::vector<std::string> getNamesUnderDir();
	
	//end must '/'
	virtual int formateDirName(std::string& dirPath);


protected:
	std::string		m_path;
};


#endif //TFILE_H
