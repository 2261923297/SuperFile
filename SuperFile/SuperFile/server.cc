#include "SuperFile.h"
#include <windows.h>
#include <string>

#define PORT 6666

int test_trans_file(const std::string& filePath, const std::string& ip) {
	int ans = 0;
	SuperFile::ptr sf = SuperFile::ptr(new SuperFile);
	
	//127.0.0.1
	//192.168.60.24
	TNet::SockDesc_t client_sock = sf->waitClient(ip.c_str(), PORT);    //accept client

	if(-1 == client_sock) {
		std::cout << "cant wait server!" << std::endl;
		return -1;
	}
	std::string save_file = "";
	int i = 1;
	while(i--) {
		std::cout << "begin send, please wait!" << std::endl;
		sf->sendFile(client_sock, filePath);                             //send

		for(int i = 0; i < 100000; i++) {
			for(int i = 0; i < 5; i++) {
				;
			}
		}
	}
	std::cout << "wait to deep" << std::endl;
	while(1) { 
		Sleep(50000);
	}
	
	return ans;
}


int main(int argc, char** argv) {
	std::string file_path = "D:\\SuperFile\\send.exe";
	std::string ip = "127.0.0.1";
	if(argc >= 2) {
		file_path = argv[1];
	}
	if(argc >= 3) {
		ip = argv[2];
	}
	test_trans_file(file_path, ip);

}
