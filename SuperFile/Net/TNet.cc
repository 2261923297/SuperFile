#include <iostream>
#include <memory>
#include <string>
#include <winsock2.h>
#include "TNet.h"

#include "../Buffer/Buffer.h"

#pragma comment(lib, "ws2_32.lib")
#define LOGOUT(ret) \
	if(ret) {       \
		std::cout << "error{ " << #ret << " } : errcode = " << GetLastError() << std::endl; \
	}

TNet::TNet() {
	WSADATA ws;
	int starRes = WSAStartup(0x22, &ws);
	LOGOUT(starRes != 0);
}
TNet::~TNet() {
	WSACleanup();
}
TNet::SockDesc_t TNet::Socket() {
	TNet::SockDesc_t sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	LOGOUT(sock == INVALID_SOCKET);
	return sock;
}

int TNet::Bind(SockDesc_t sock, const char* ip_addr, short port) {
	int ans = 0;
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int bindRet = bind(sock, (sockaddr*)&addr, sizeof(addr));
	LOGOUT(bindRet == SOCKET_ERROR);
	ans = bindRet;
	return ans;
}
int TNet::Listen(TNet::SockDesc_t sock, int num) {
	int ans = 0;
	int listenRet = listen(sock, num);
	LOGOUT(listenRet == SOCKET_ERROR);
	ans = listenRet;
	return ans;
}
TNet::SockDesc_t TNet::Accept(TNet::SockDesc_t sock) {
	SockDesc_t clientSock = 0;
	sockaddr_in addrClient;
	int len = sizeof(addrClient);
	clientSock = accept(sock, (sockaddr*)&addrClient, &len);
	LOGOUT(clientSock == INVALID_SOCKET);
	
	return clientSock;
}
int TNet::Connect(TNet::SockDesc_t sock, const char* ip, short port) {
	int ans = 0;
	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_port = htons(port);
	memset(serverAddr.sin_zero, 0x00, 8);


	int connRet = connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	LOGOUT(connRet == SOCKET_ERROR);

	return connRet;
}
TNet::DataSize_t TNet::RecvData(TNet::SockDesc_t sock, void* buffer, int size){
	DataSize_t ans = 0;
	int readSize = 0;
	readSize = recv(sock, (char*)buffer, size, 0);
	((char*)buffer)[size] = '\0';
	

	LOGOUT(readSize == SOCKET_ERROR);
	ans = readSize;
	return ans;
}
TNet::DataSize_t TNet::SendData(TNet::TNet::SockDesc_t sock, void* buffer, int size){

	TNet::DataSize_t ans = 0;
	int writeSize = send(sock, (char*)buffer, size, 0);

	LOGOUT(writeSize == SOCKET_ERROR);
	ans = writeSize;
	return ans;
}

