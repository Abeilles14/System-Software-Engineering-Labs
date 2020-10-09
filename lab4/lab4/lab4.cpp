#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")		// winsock library

int main() {
	WSADATA WSAData;
	SOCKET sock;
	SOCKET csock = 0;
	SOCKADDR_IN sin;
	SOCKADDR_IN csin;

	WSAStartup(MAKEWORD(2, 0), &WSAData);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(23);
	bind(sock, (SOCKADDR*)& sin, sizeof(sin));

	listen(sock, 0);
	int val = 0;
	
	while (1) {
		int sizeof_csin = sizeof(csin);
		val = accept(sock, (SOCKADDR*)& csin, &sizeof_csin);

		if (val != INVALID_SOCKET) {
			send(csock, "Hello world!\r\n", 14, 0);
			closesocket(csock);
		}
	}

	closesocket(sock);
	WSACleanup();		// cleanup sockets

	return 0;
}