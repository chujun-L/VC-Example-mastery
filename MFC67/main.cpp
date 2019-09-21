#pragma comment(lib,"ws2_32.lib")

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

using namespace std;

int main()
{
	WSADATA wsaData;
	SOCKET ListeningSocket;
	SOCKET ConnectionSocket;
	SOCKADDR_IN ServerAddr;
	SOCKADDR_IN ClientAddr;
	char RecvBuf[1024] = {0};
	char ClientAddrBuf[16] = {0};
	// sizof(SOCKADDR_IN) = 16，所以初始化ClientAddrLen时不能小于16
	int ClientAddrLen = 16;
	int Port = 5010;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup() failed" << endl;
		return -1;
	}
	
	ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListeningSocket == INVALID_SOCKET) {
		cout << "socket() failed" << endl;
		WSACleanup();
		return -1;
	}
	
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (bind(ListeningSocket, (sockaddr *)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		cout << "bind() failed" << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return -1;
	}
	
	if (listen(ListeningSocket, 5) == SOCKET_ERROR) {
		cout << "listen() failed" << endl;
		closesocket(ListeningSocket);
		WSACleanup();
		return -1;
	}
	
	while (1) {
		cout << "accepting..." << endl;
		ConnectionSocket = accept(ListeningSocket, (sockaddr *)& ClientAddr, &ClientAddrLen);
		if (ConnectionSocket == INVALID_SOCKET) {
			cout << "accept() failed" << endl;
			closesocket(ListeningSocket);
			WSACleanup();
			return -1;
		}

		inet_ntop(AF_INET, &ClientAddr.sin_addr, ClientAddrBuf, 16);
		cout << "accepted client IP: " << ClientAddrBuf << " Port: " << ntohs(ClientAddr.sin_port) << endl;

		cout << "Receiving..." << endl;
		if (recv(ConnectionSocket, RecvBuf, sizeof(RecvBuf), 0) == SOCKET_ERROR) {
			cout << "recv() failed" << endl;
			closesocket(ConnectionSocket);
			WSACleanup();
			return -1;
		}

		cout << "received: " << RecvBuf << endl;
		memset(RecvBuf, 0, sizeof(RecvBuf));

		closesocket(ConnectionSocket);
	}

	WSACleanup();

	system("pause");
	return 0;
}