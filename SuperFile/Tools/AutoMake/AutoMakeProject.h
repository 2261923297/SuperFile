#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include "../../File/TWinFile.h"

class AutoMakeProject {
public:
	typedef std::shared_ptr<AutoMakeProject> ptr;
	AutoMakeProject(const std::string& rootPath, const std::string& projectName);

	~AutoMakeProject();

	const std::string& getRootPath() {	return m_rootPath; }

	const std::string& getprojectName() { return m_projectName;	}

	void setRootPath(const std::string& rootPath) {	m_rootPath = rootPath; }

	void setProjectName(const std::string& projectName) { m_projectName = projectName; }


	int run(const std::string& projectName = "");
protected:
	std::string init();

	int initProjectFile();
protected:
	TFile::ptr m_fileTool;

	std::string m_rootPath;
	std::string m_projectName;

	std::vector<std::string> m_files;
};
