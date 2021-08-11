#pragma once 
#include <memory>
#include <string> 
#include "../Net/TNet.h"
#include "../File/TFile.h"
#include "../File/TWinFile.h"

class SuperFile {
public:
	typedef std::shared_ptr<SuperFile> ptr;
	SuperFile();
	virtual ~SuperFile();

	int sendInit(const std::string& save_path = "");

	int recvInit(std::string& save_path);
	
	int sendFile(TNet::SockDesc_t sock, const std::string& file_path);

	int recvFile(TNet::SockDesc_t sock, const std::string& save_path);

	TNet::SockDesc_t waitClient(const std::string& ip, const short port);

	int searchServer(const std::string& ip, const short port);


protected:
	TFile::ptr m_file;
//	TLog::ptr m_log;
	TNet::ptr  m_net;

//	Promission::ptr m_promission;
private:
	TNet::SockDesc_t m_sock;

};
