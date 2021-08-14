#include "TWinFile.h"
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
//	ShowFileData(file_data);

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
//------------------------------WinFile----------------------------\\


std::string TWinFile::getParent(const std::string& fileName) {
	std::string ans = "";
	if(fileName.size() == 0) {
		ans = m_path;
	} else {
		ans = fileName;
	}
	if(ans[ans.size() - 1] == DIR_SEPARATOR) {
		ans.pop_back();
	}
	return ans.substr(0, ans.find_last_of(DIR_SEPARATOR) + 1);
}

uint64_t TWinFile::getFileSize() {
	return m_fileData.size;
}

int TWinFile::isDir()   {
	return _A_SUBDIR == m_fileData.attrib;
}


int TWinFile::createFile(const char* path)   {
	FILE* pFile = fopen(path, "ab+");
	fclose(pFile);
	if(pFile == nullptr) {
		perror("TWinFile::createFile");
		std::cout << "path: " << path << std::endl;
	}
	return pFile != NULL;
}

int TWinFile::createDir(const char* path)   {
	std::string str_path = path;
	formateDirName(str_path);          // end must '\'
	std::list<std::string> l_dirs;
	
	int beg = 3, len = 0;
	std::string cur_dir_name;
	if(str_path.size() < beg + 1) {
		std::cout << "dir format err!" << std::endl;
		return -1;
	}
	for(size_t i = beg + 1; i < str_path.size(); i++) {
		if(str_path[i] == DIR_SEPARATOR) {
			len = i - beg;
			cur_dir_name = str_path.substr(beg, len);
			beg = i + 1;

			l_dirs.push_back(cur_dir_name);
		}
	}
	int mkdirRes = 0;
	std::string dirs = str_path.substr(0, 2);
	while( l_dirs.size() != 0 && -1 != mkdirRes) {
		dirs += '\\';
		dirs += l_dirs.front();
		l_dirs.pop_front();
		mkdirRes = 0;
		if(-1 == _access(dirs.c_str(), 0)) {
			mkdirRes = _mkdir(dirs.c_str());
		}
	}

	if(-1 == _access(path, 0)) {
		std::cout << "create dir error!" 
			<< " path = " << path << "errmsg: ";
			
		perror("create dir");

	}
	return 0;
}

std::vector<std::string> TWinFile::getNamesUnderDir()   {
	std::vector<std::string> subNames;
	std::cout << "m_path: " << m_path;
	if(isDir()) {
		std::cout << " is Dir" << std::endl;
		_finddata_t fileData;
		int k;
		long Handle;
		formateDirName(m_path);
		std::string queryPath = m_path + "*.*";
		std::cout << "queryPath: " << queryPath << std::endl;
		
		k = Handle = _findfirst(queryPath.c_str(), &fileData);
		while(k != -1) {
			std::cout << "k = " << k << std::endl;
			subNames.push_back(std::string(fileData.name));
			k = _findnext(Handle, &fileData);
			//_findclose(Handle);
		}
	} else {
		std::cout << " is not Dir!" << std::endl;
	}
	return subNames;
}

//end must '/'
int TWinFile::formateDirName(std::string& dirPath)   {
	if(dirPath.size() && dirPath[dirPath.size() - 1] != DIR_SEPARATOR) {
		dirPath += DIR_SEPARATOR;
		return 1;
	}
	return 0;
}

int TWinFile::TWinFile::isExit() {
	return -1 != _access(m_path.c_str(), 0);
}



