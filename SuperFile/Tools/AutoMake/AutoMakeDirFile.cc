#include "../../File/TFile.h"
#include "../../File/TWinFile.h"

class AutoMakeDirFile {
public:
	AutoMakeDirFile(const std::string& rootDir) {
		m_fileTool =TFile::ptr(new TWinFile());
		m_rootDir = rootDir;
	}
	int addDir(const std::string& dirPath) {
		return m_dirs.push_back(dirPath);
	}
	int addFile(const std::string filePath) {
		return m_files.push_back(filePath);
	}

	int run() {

	}
	~AutoMakeDirFile() { }
private:
	TFile::ptr m_fileTool;
	std::string m_rootDir;
	std::vector<std::string> m_dirs;
	std::vector<std::string> m_files;
}
