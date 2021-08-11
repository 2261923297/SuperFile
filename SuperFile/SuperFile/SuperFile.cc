#include "SuperFile.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
SuperFile::SuperFile() {
	m_file = TFile::ptr(new TWinFile("C:\\"));
	m_net = TNet::ptr(new TNet);

	m_sock = TNet::Socket();

}
SuperFile::~SuperFile() {
	std::cout << "SuperFile out" << std::endl;
}



int SuperFile::sendInit(const std::string& save_path) {
	int ans = -1;
	TNet::DataSize_t nSend = 0;
	TNet::DataSize_t nRecv = 0;
	char recvResult = '\0';


	std::string head = "0SF";
	std::string args = "save_abs:";
	std::string data = save_path.size() ? (head + save_path) : head;

	nSend = TNet::SendData(m_sock, data.c_str(), data.size());
	if(nSend == -1) {
		ans = -1; 
		return ans;
	}
	nRecv = TNet::RecvData(m_sock, &recvResult, 1);
	if(-1 == nRecv) {
		ans = -1;
		return ans;
	}
	if(recvResult == '1') {
		ans = 1;
	}
	
	std::cout << "OSF, could send!" << std::endl;
	return ans;
}

int SuperFile::recvInit(std::string& save_path) {
	int ans = 0;
	TNet::DataSize_t nRecv = 0, nSend = 0;
	char recvBuffer[1024] = { 0 };
	
	static std::string server_head = "0SF";
	static std::string server_arg_savePath = "save_abs:";
	static int savePathArgSize = sizeof(server_arg_savePath);

	nRecv = TNet::RecvData(m_sock, recvBuffer, 1024);
	if(nRecv == -1) {
		ans = -1;
		return ans;
	}
	std::string head(recvBuffer, 3);
	if(!(head == server_head)) {
		ans = -1;
		return ans;
	}
	if(nRecv > 3) {
		save_path = std::string(recvBuffer, 3, 1024);
	}
	std::cout << "recvFile && save_as " << save_path << std::endl; 

	nSend = TNet::SendData(m_sock, "1", 1);
	return ans;
}

int SuperFile::sendFile(TNet::SockDesc_t sock, const std::string& file_path) {
	
	int ans = 0;

	std::cout << "begin send..." << std::endl;
	FILE* pFile_s = fopen(file_path.c_str(), "rb+");	
	if(nullptr == pFile_s) {
		std::cout << "can^t open file: "
 << file_path << std::endl;
	}
	fseek(pFile_s, 0, SEEK_SET);

	int carSize = 1024;
	char fileCar[1025] = { 0 };
	memset(fileCar, 0, 1025);

	int nSend = 0, nRead = 0;
	
	int send_times = 0;
	TNet::SockDesc_t client_sock = m_sock;
	do {
		nRead = fread(fileCar, 1, carSize, pFile_s);
		fileCar[nRead] = '\0';
		nSend = m_net->SendData(client_sock, fileCar, nRead);
		memset(fileCar, 0, 1025);
		//std::cout << "nSend = " << nSend << std::endl;
		send_times++;
	} while(nRead == carSize);
	//close(client_sock);
	std::cout << "SendSize = " << (send_times - 1) * carSize + nSend << std::endl;
	return ans;
}

int SuperFile::recvFile(TNet::SockDesc_t sock, const std::string& save_path) {
	int ans = 0;

	std::cout << "begin recv..." << std::endl;
	int carSize = 1024;
	char fileCar[1025] = { 0 };
	int nRecv = 0, nWrite = 0, recv_nums = 0, write_nums = 0;

	std::string sp_parent = save_path.substr(0, save_path.find_last_of('\\'));
	m_file->createDir(sp_parent.c_str());
	m_file->createFile(save_path.c_str());

	FILE* pFile_r = fopen(save_path.c_str(), "wb+");
	if(nullptr == pFile_r) {
		std::cout << "can^t fopen file to write: " << save_path << std::endl;
		return -1;
	}

	do {
		nRecv = m_net->RecvData(m_sock, fileCar, carSize);
		nWrite = fwrite(fileCar, 1, nRecv, pFile_r);
		recv_nums += nRecv;
		write_nums += write_nums;
		std::cout << "nRecv = " << nRecv << std::endl;
	} while(nRecv != -1);
	std::cout << "recv_nums = " << recv_nums << "  write_nums = " << write_nums << std::endl;
	return ans;
}

TNet::SockDesc_t SuperFile::waitClient(const std::string& ip, const short port) {
	if(m_sock > 0) {
		close(m_sock);
		m_sock = 0;
	}
	m_sock = TNet::Socket();
	std::cout << "init_sock = " << m_sock << std::endl;

	TNet::Bind(m_sock, ip.c_str(), port);
	TNet::Listen(m_sock, 512);

	std::cout << "Keep wait client..." << std::endl;
	TNet::SockDesc_t client_sock = TNet::Accept(m_sock);
	if(0 != client_sock) {
		std::cout << "accept client: sock = " << client_sock << std::endl;
	} else {
		std::cout << "err accept" << std::endl;
	} 
	close(m_sock);
	m_sock = client_sock;
	return client_sock;
}


int SuperFile::searchServer(const std::string& ip, const short port){
	if(m_sock > 0) {
		close(m_sock);
		m_sock = 0;
	}
	m_sock = TNet::Socket();
	std::cout << "connect ip = " << ip << ", port = " << port << std::endl;
	return TNet::Connect(m_sock, ip.c_str(), port);
}


