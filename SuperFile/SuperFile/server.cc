#include "SuperFile.h"
#include <windows.h>
int test_trans_file() {
	int ans = 0;
	SuperFile::ptr sf = SuperFile::ptr(new SuperFile);
	
	//127.0.0.1
	//192.168.60.24
	TNet::SockDesc_t client_sock = sf->waitClient("127.0.0.1", 6666);

	if(-1 == client_sock) {
		std::cout << "cant wait server!" << std::endl;
		return -1;
	}
	std::string save_file = "";
	int i = 1;
	while(i--) {
		std::cout << "begin send, please wait!" << std::endl;
		sf->sendFile(0, "C:\\a.exe");
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


int main() {
	test_trans_file();
}
