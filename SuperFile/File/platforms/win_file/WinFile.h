#ifndef __WINFILE_H_
#define __WINFILE_H_

#include <iostream>
#include <direct.h>
#include <map>
#include <string>
class WinFile {
public:
	typedef struct _finddata_t FileData_t;

	static FileData_t GetFileData(const char* path);

	static FileData_t GetFileData(const std::string& path) { return GetFileData(path.c_str()); }

	static void ShowFileData(const FileData_t& data);

public:
	static std::map<unsigned int, std::string> s_file_desc_mapper;
};

	
#endif //__WINFILE_H_
