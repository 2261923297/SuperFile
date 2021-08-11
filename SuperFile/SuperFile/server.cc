#include "SuperFile.h"

int test_trans_file() {
	int ans = 0;
	SuperFile::ptr sf = SuperFile::ptr(new SuperFile);
	
	TNet::SockDesc_t client_sock = sf->waitClient("192.168.60.24", 6666);

	if(-1 == client_sock) {
		std::cout << "cant wait server!" << std::endl;
		return -1;
	}
	std::string save_file = "";
	int i = 1;
	while(i--) {
		sf->sendFile(0, "C:\\a.iso");
		std::cout << "sending... please wait" << std::endl;

		for(int i = 0; i < 100000; i++) {
			for(int i = 0; i < 5; i++) {
				;
			}
		}
	}
	return ans;
}


int main() {
	test_trans_file();
}
