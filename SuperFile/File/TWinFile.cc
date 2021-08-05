#include "TWinFile.h"


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

			std::cout << "cur_dir_name = " << cur_dir_name << std::endl;
			l_dirs.push_back(cur_dir_name);
		}
	}
	int mkdirRes = 0;
	std::cout << "str_path" << str_path << std::endl;
	std::string dirs = str_path.substr(0, 2);
	while( l_dirs.size() != 0 && -1 != mkdirRes) {
		std::cout << "dirs f = " << dirs << std::endl;
		dirs += '\\';
		dirs += l_dirs.front();
		l_dirs.pop_front();
		std::cout << "dirs b = " << dirs << std::endl;	
		mkdirRes = 0;
		if(-1 == _access(dirs.c_str(), 0)) {
			mkdirRes = _mkdir(dirs.c_str());
		}
		else {
			std::cout << "dir: " << dirs.c_str() << "isExit" << std::endl;
		}
	}

	std::cout << "createDir success!" << std::endl;
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
	/*
	if(isDir()) {
		_finddata_t file;
		int k;
		long HANDLE;

		std::cout << "m_filePath is a dir!" << std::endl;
		formateDirName(m_path);
		std::cout < "formate m_filePath: " << m_path << std::endl;
		m_path += "*.*";
		std::cout << "getNamesUndjerDir: dirCmd = " << m_path; 
		
		k = HANDLE = _findfirst(m_path.c_str(), &file);	
		while (k != -1) {
			subNames.push_back(std::string(file.name));
			k = _findnext(HANDLE, &file);
		}
		_findclose(HANDLE);
	} else {
		std::cout << "m_path: " << m_path << " is not a dir!" << std::endl;
	}
	*/
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




