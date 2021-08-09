#pragma once 
#include <memory>
#include <std::string> 

class SuperFile {
public:
	typedef std::shared_ptr<SuperFile> ptr;
	SuperFile();
	virtual ~SuperFile();

	virtual int initPromission();

	virtual int init();

	virtual int createFile();

	virtual int readAllFile();

	virtual int sendFile();

	virtual int recvFile();

protected:
	TFile::ptr m_file;
	TLog::ptr m_log;
	TNet::pt m_net;

	Promission::ptr m_promission;
private:


};
