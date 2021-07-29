#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <memory>

class TFile {
public:
	typedef std::shared_ptr<TFile> ptr;
	TFile() {};
	~TFile() {};

	static int isExit(const char* path);

	static int isDir(const char* path);

	static int creadFile(const char* path, const char* fileName);

	static int creadDir(const char* path, const char* dirName);

	static std::vector<std::string> getNamesUnderDir(const char* dirPath);
	
	//end must '/'
	static int formatDirName(const std::string& dirPath);

	static int formatDirName(const char* dirPath);

private:





};

