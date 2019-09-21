#pragma comment(lib,"ws2_32.lib")

#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <WS2tcpip.h>

using namespace std;

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "WSAStartup() failed" << endl;
		WSACleanup();
		return -1;
	}

	SOCKET s;
	SOCKADDR_IN ServerAddr;
	int Port = 5010;
	//const char *ServerIP = "127.0.0.1";
	//char ServerIPBuf[16] = { 0 };

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		cout << "socket() failed" << endl;
		system("pause");
		WSACleanup();
		return -1;
	}

	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	inet_pton(AF_INET, "127.0.0.1", &ServerAddr.sin_addr);

	if (connect(s, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		cout << "connect() failed" << endl;
		closesocket(s);
		WSACleanup();
		return -1;
	} else {
		cout << "connect() success" << endl;
	}

	send(s, "hello", 5, 0);

	WSACleanup();

	system("pause");
	return 0;
}