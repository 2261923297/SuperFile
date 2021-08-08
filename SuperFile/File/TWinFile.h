#pragma once
#include "TFile.h"
#include "platforms/win_file/WinFile.h"
#include <io.h>
#include <direct.h>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include <stdio.h>
#define DIR_SEPARATOR '\\'
class TWinFile : public TFile {
public:
	typedef WinFile::FileData_t FileData_t;
	typedef std::shared_ptr<TWinFile> ptr;
//	using DirSeparator = DIR_SEPARATOR;

	TWinFile(const std::string& filePath = "C:\\") : TFile(filePath) {
		m_fileData = getFileData();
	}
	~TWinFile() {

	}
	int isDir() override;

	int isExit() override;
	
	int createFile(const char* path) override;

	int createDir(const char* path) override;


	std::vector<std::string> getNamesUnderDir() override;

	int formateDirName(std::string& dirPath) override;

	

protected:
	FileData_t getFileData() {
		return WinFile::GetFileData(m_path.c_str());
	}
private:
	FileData_t m_fileData;
};
