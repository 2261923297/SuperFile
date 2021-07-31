#ifndef TFILE_H
#define TFILE_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <memory>

#define DIR_SEPARATOR '\\'


class TFile {
public:
	typedef std::shared_ptr<TFile> ptr;
	
	TFile();
	~TFile();
	
	static int isExit(const char* path);

	static int isDir(const char* path);

	static int creadFile(const char* path, const char* fileName);

	static int creadDir(const char* path, const char* dirName);

	static std::vector<std::string> getNamesUnderDir(const char* dirPath);
	
	//end must '/'
	static int formatDirName(std::string& dirPath);

	static std::string formatDirName(const char* dirPath);

	static int Mkdir(const char*) {
	
	}
private:





};


#endif //TFILE_H
