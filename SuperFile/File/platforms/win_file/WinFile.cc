#include "WinFile.h"
#include <time.h>

std::map<unsigned int, std::string> WinFile::s_file_desc_mapper = {
      { _A_ARCH, "cun dang" }
	, { _A_NORMAL, "normal" }
	, { _A_HIDDEN, "hidden"}
	, { _A_RDONLY, "read only" }
	, { _A_SUBDIR, "dir" }
	, { _A_SYSTEM, "system" }
};


WinFile::FileData_t WinFile::GetFileData(const char* path) {
	WinFile::FileData_t file_data;
	
	file_data = {
		0
	};
	
	int k;
	long f_handle;
	std::cout << "WinFile::GetFileData: " << path << std::endl;
	k = f_handle = _findfirst(path, &file_data);
	ShowFileData(file_data);

	_findclose(f_handle);
	return file_data;
}


void WinFile::ShowFileData(const FileData_t& data) {
	char createTime[128] = { 0 };
	char accessTime[128] = { 0 };
	char writeTime[128] = {	0 };
#define xx(saveStr, timep) \
	strftime((char*)saveStr, 128, "%Y-%m-%d, %H:%M:%S", gmtime((time_t*)timep))
	xx(createTime, &data.time_create);
	xx(accessTime, &data.time_access);
	xx(writeTime, &data.time_write);
	
	std::cout << "find_data: "
		<< "\n\tattrib = " << data.attrib << " desc: " << WinFile::s_file_desc_mapper[data.attrib]
		<< "\n\tcreate_time: " << createTime
		<< "\n\taccess_time: " << accessTime
		<< "\n\twrite_time: " << writeTime
		<< "\n\tsize = " << data.size
		<< "\n\tname = " << data.name
		<< std::endl;

}




