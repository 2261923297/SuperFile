#include <iostream>
#include "../TNet.h"
#include <string>
#include <winsock2.h>
#include <thread>
#pragma comment(lib, "ws2_32.lib")
int clientThread() {
	TNet nt;
	SOCKET clientSock = nt.Socket();
	nt.Connect(clientSock, "127.0.0.1", 8888);
	
	std::string str = "Hello, Server!";
	int SendSize = 0;
	while(SendSize != SOCKET_ERROR) {
		for(int i = 0; i < 10000; i++) 
		{
			;
		}
		SendSize = nt.SendData(clientSock, (void*)str.c_str(), str.size());
		
	}


}

int serverThread() {
	TNet nt;
	TNet::SockDesc_t serverSock = nt.Socket();
	nt.Bind(serverSock, "127.0.0.1", 8888);

	nt.Listen(serverSock, 512);
	TNet::SockDesc_t clientSock = nt.Accept(serverSock);

	int recvRet = 0;
	char recvBuffer[1024] = { 0 };
	memset(recvBuffer, 0, 1024);
	
	while(SOCKET_ERROR != recvRet) {
		recvRet = nt.RecvData(clientSock, recvBuffer, 1023);
		if(recvRet != SOCKET_ERROR) {
			recvBuffer[recvRet] = '\0';
			std::cout << recvBuffer << std::endl;
			memset(recvBuffer, 0, 1024);
		}
	}
}

/*
int main() {
	//std::cout << "Hello, I am Client!" << std::endl;
	std::Thread clientThrd(clientThread);
	std::THread serverThrd(serverThread);

	clientThrd.detach();
	serverThed.detach();

	std::cout << "---------------detached-----------" << std::endl;
	while(1) {

	}



	return 0;
}
*/
