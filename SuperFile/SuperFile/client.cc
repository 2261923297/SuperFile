#include "SuperFile.h"
#include <windows.h>

#define PORT 6666

int test_trans_file(const std::string& filePath, std::string& ip) {
	int ans = 0;
	SuperFile::ptr sf = SuperFile::ptr(new SuperFile);
<<<<<<< HEAD
	if( -1 == sf->searchServer("192.168.60.24", 6666)) {
=======
	if( -1 == sf->searchServer(ip.c_str(), PORT)) {           //connect
>>>>>>> 461766edd0db2a4732eb99f24cd32a533b3ac0bd
		std::cout << "cant search server!" << std::endl;
		return -1;
	}
	
	std::string recv_file = "";
	int i = 1;
	while(i--) {
		recv_file = "...";
<<<<<<< HEAD
		sf->recvFile(0, "D:\\SuperFile\\recv.iso");
=======
		sf->recvFile(sf->getSock(), filePath);                     //recv
>>>>>>> 461766edd0db2a4732eb99f24cd32a533b3ac0bd
		std::cout << "recvFile: " << recv_file << std::endl;
	
		for(int i = 0; i < 100000; i++) {
			for(int j = 0; j < 5; j++) {
				;
			}
		}
	}
	return ans;
}

int main(int argc, char** argv) {
	std::string file_path = "D:\\SuperFile\\recv.exe";
	std::string ip = "127.0.0.1";
	if(argc > 2) {
		file_path = argv[1];
	}
	if(argc > 3) {
		ip = argv[2];
	}
	test_trans_file(file_path, ip);
}
