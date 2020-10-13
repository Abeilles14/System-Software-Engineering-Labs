#include <stdio.h>
#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")		//link with ws2_32.lib library

// Function prototype
void StreamClient(char* szServer, short nPort);

// Helper macro for displaying errors
#define PRINTERROR(s) fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())

int main(int argc, char** argv) {
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int nRet;
	short nPort;

	//
	// Check for the host and port arguments
	//
	if (argc != 3)
	{
		fprintf(stderr, "\nSyntax: client ServerName PortNumber\n");
		return 0;
	}

	nPort = atoi(argv[2]);


	//
	// Initialize WinSock and check the version
	//
	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (wsaData.wVersion != wVersionRequested)
	{
		fprintf(stderr, "\n Wrong version\n");
		return 0;
	}


	//
	// Go do the stuff a stream client does
	//
	StreamClient(argv[1], nPort);


	//
	// Release WinSock
	//
	WSACleanup();

	return 0;
}

void StreamClient(char* szServer, short nPort)
{
	printf("\nStream Client connecting to server: %s on port: %d",
		szServer, nPort);

	//
	// Find the server
	//
	LPHOSTENT lpHostEntry;

	lpHostEntry = gethostbyname(szServer);
	if (lpHostEntry == NULL)
	{
		PRINTERROR("gethostbyname()");
		return;
	}

	//
	// Create a TCP/IP stream socket
	//
	SOCKET	theSocket;
	
	theSocket = socket(AF_INET,// Address family
		SOCK_STREAM,// Socket type
		IPPROTO_TCP);		// Protocol
	if (theSocket == INVALID_SOCKET)
	{
		PRINTERROR("socket()");
		return;
	}

	//
	// Fill in the address structure
	//
	SOCKADDR_IN saServer;

	saServer.sin_family = AF_INET;

	// Server's address
	saServer.sin_addr = *((LPIN_ADDR)* lpHostEntry->h_addr_list);
	saServer.sin_port = htons(nPort);	// Port number from command line

	//
	// connect to the server
	//
	int nRet;

	nRet = connect(theSocket,	// Socket
		(LPSOCKADDR)& saServer,	// Server address
		sizeof(struct sockaddr));// Length of server address structure
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("socket()");
		closesocket(theSocket);
		return;
	}


	//
	// Send data to the server
	//
	char szBuf[256];

	strcpy_s(szBuf, "From the Client");
	nRet = send(theSocket,// Connected socket
		szBuf,	// Data buffer
		strlen(szBuf),	// Length of data
		0);	// Flags
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("send()");
		closesocket(theSocket);
		return;
	}


	//
	// Wait for a reply
	//
	nRet = recv(theSocket, // Connected socket
		szBuf,	// Receive buffer
		sizeof(szBuf),	// Size of receive buffer
		0);	// Flags
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("recv()");
		closesocket(theSocket);
		return;
	}


	//
	// Display the received data
	//

	szBuf[nRet] = 0;
	printf("\nData received: %s", szBuf);


	closesocket(theSocket);

	return;
}