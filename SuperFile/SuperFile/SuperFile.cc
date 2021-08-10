#include "SuperFile.h"
#include <time.h>
#include <string.h>
SuperFile::SuperFile() {
	m_file = TFile::ptr(new TWinFile("C::\\"));
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

int SuperFile::sendFile(const std::string& file_path) {
	
	int ans = 0;
	ans = sendInit();
	if(ans == -1) {
		return ans;
	}
	std::cout << "begin send..." << std::endl;
	FILE* pFile_s = fopen(file_path.c_str(), "rb+");	
	if(nullptr == pFile_s) {
		std::cout << "can^t open file: " << file_path << std::endl;
	}

	int carSize = 1024;
	char fileCar[1025] = { 0 };
	int nSend = 0;
	int nRead = 0;
	
	TNet::SockDesc_t client_sock = m_sock;
	do {
		nRead = m_file->readData(fileCar, carSize, pFile_s);
		fileCar[nRead] = '\0';
		nSend = m_net->SendData(client_sock, fileCar, nRead);
		memset(fileCar, 0, 1025);
		std::cout << "nSend = " << nSend << std::endl;
	} while(nRead == carSize);

	return ans;
}

int SuperFile::recvFile() {
	int ans = 0;
	std::string save_path = "";
	ans = recvInit(save_path);
	if(ans == -1) {
		return ans;
	}
	std::cout << "begin recv..." << std::endl;
	int carSize = 1024;
	char fileCar[1025] = { 0 };
	int nRecv = 0;
	int nWrite = 0;
	if(save_path.size() == 0) {
		time_t now = time(&now);
		struct tm* info = localtime(&now);

		char fileName[128] = { 0 };
		memset(fileName, 0, 128);
		fileName[0] = 'r';
		strftime(fileName + 1, 127, "%Y_%m_%d_%H_%M_%S", info);

//		std::string fileName = "";

	
		save_path = std::string("D:\\SuperFile\\Recv\\");
		m_file->createDir(save_path.c_str());
		save_path = save_path + fileName + ".png";
	}
	m_file->createFile(save_path.c_str());

	FILE* pFile_r = fopen(save_path.c_str(), "wb+");
	if(nullptr == pFile_r) {
		std::cout << "can^t fopen file to write: " << save_path << std::endl;
		return -1;
	}

	do {
		nRecv = m_net->RecvData(m_sock, fileCar, carSize);
		nWrite = m_file->writeData(fileCar, nRecv, pFile_r);
		std::cout << "nRecv = " << nRecv << std::endl;
	} while(nRecv != -1);

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


