#include "TFile.h"
#include "platforms/win_file/WinFile.h"
#include <memory>
#include <string>
#include <vector>
#include <stdio.h>
#define DIR_SEPARATOR '\\'
class TWinFile : public TFile {
public:
	typedef WinFile::FileData_t FileData_t;
	typedef std::shared_ptr<TWinFile> ptr;
	
	TWinFile(const std::string& filePath) : TFile(filePath) {
		m_fileData = getFileData();
	}
	~TWinFile() {

	}

	int isExit() override {
		return !!m_fileData.size;
	}

	int isDir() override {
		return _A_SUBDIR == m_fileData.attrib;
	}

	int createFile(const char* path) override {
		FILE* pFile = fopen(path, "rb+");
		fclose(pFile);

		return pFile != NULL;
	}

	int createDir(const char* path) override {
		return _mkdir(path);
	}

	std::vector<std::string> getNamesUnderDir() override {
		std::vector<std::string> subNames;
		if(isDir()) {
			_finddata_t file;
			int k;
			long HANDLE;
			formateDirName(m_path);
			m_path += "*.*";
			std::cout << "getNamesUndjerDir: dirCmd = " << m_path; 
			
			k = HANDLE = _findfirst(m_path.c_str(), &file);	
			while (k != -1)
			{
				subNames.push_back(std::string(file.name));
				k = _findnext(HANDLE, &file);
			}
			_findclose(HANDLE);
		}
		
	}
	
	//end must '/'
	int formateDirName(std::string& dirPath) override {
		if(dirPath.size() && dirPath[dirPath.size() - 1] != DIR_SEPARATOR) {
			dirPath += DIR_SEPARATOR;
			return 1;
		}
		return 0;
	}

protected:
	FileData_t getFileData() {
		return WinFile::GetFileData(m_path.c_str());
	}
private:
	FileData_t m_fileData;
};
