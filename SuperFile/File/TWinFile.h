#pragma once
#include "TFile.h"
#include <io.h>
#include <direct.h>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include <stdio.h>
#include <map>

#define DIR_SEPARATOR '\\'

class WinFile {
public:
	typedef struct _finddata_t FileData_t;

	static FileData_t GetFileData(const char* path);

	static FileData_t GetFileData(const std::string& path) { return GetFileData(path.c_str()); }

	static void ShowFileData(const FileData_t& data);

public:
	static std::map<unsigned int, std::string> s_file_desc_mapper;
};

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

	std::string getParent(const std::string& fileName = "") override;

	uint64_t getFileSize() override;

	std::vector<std::string> getNamesUnderDir() override;

	int formateDirName(std::string& dirPath) override;

	

protected:
	FileData_t getFileData() {
		return WinFile::GetFileData(m_path.c_str());
	}
private:
	FileData_t m_fileData;
};
