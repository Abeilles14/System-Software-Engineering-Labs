#include <stdio.h>
#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")		//link with ws2_32.lib library

void StreamServer(short nPort);

#define PRINTERROR(s) fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())		// Helper macro for displaying errors

int main(int argc, char** argv) {
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int nRet;
	short nPort;

	if (argc != 2)				// check port arg
	{
		fprintf(stderr, "\nSyntax: server PortNumber\n");
		return 0;
	}

	nPort = atoi(argv[1]);

	nRet = WSAStartup(wVersionRequested, &wsaData);		// init winsock and chek version
	if (wsaData.wVersion != wVersionRequested)
	{
		fprintf(stderr, "\n Wrong version\n");
		return 0;
	}


	//
	// Do the stuff a stream server does
	//
	StreamServer(nPort);


	//
	// Release WinSock
	//
	WSACleanup();

	return 0;
}

void StreamServer(short nPort)
{
	//
	// Create a TCP/IP stream socket to "listen" with
	//
	SOCKET	listenSocket;

	listenSocket = socket(AF_INET,			// Address family
		SOCK_STREAM,		// Socket type
		IPPROTO_TCP);		// Protocol
	if (listenSocket == INVALID_SOCKET)
	{
		PRINTERROR("socket()");
		return;
	}


	//
	// Fill in the address structure
	//
	SOCKADDR_IN saServer;

	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;	// Let WinSock supply address
	saServer.sin_port = htons(nPort);		// Use port from command line

	//
	// bind the name to the socket
	//
	int nRet;

	nRet = bind(listenSocket,	// Socket 
		(LPSOCKADDR)& saServer,	// Our address
		sizeof(struct sockaddr));// Size of address structure
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("bind()");
		closesocket(listenSocket);
		return;
	}

	//
	// This isn't normally done or required, but in this 
	// example we're printing out where the server is waiting
	// so that you can connect the example client.
	//
	int nLen;
	nLen = sizeof(SOCKADDR);
	char szBuf[256];

	nRet = gethostname(szBuf, sizeof(szBuf));
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("gethostname()");
		closesocket(listenSocket);
		return;
	}

	//
	// Show the server name and port number
	//
	printf("\nServer named %s waiting on port %d\n",
		szBuf, nPort);

	//
	// Set the socket to listen
	//

	printf("\nlisten()");
	nRet = listen(listenSocket,	// Bound socket
		SOMAXCONN);	// Number of connection request queue
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("listen()");
		closesocket(listenSocket);
		return;
	}

	//
	// Wait for an incoming request
	//
	SOCKET	remoteSocket;

	printf("\nBlocking at accept()");
	remoteSocket = accept(listenSocket,  // Listening socket
		NULL,	// Optional client address
		NULL);
	if (remoteSocket == INVALID_SOCKET)
	{
		PRINTERROR("accept()");
		closesocket(listenSocket);
		return;
	}

	//
	// We're connected to a client
	// New socket descriptor returned already
	// has clients address

	//
	// Receive data from the client
	//
	memset(szBuf, 0, sizeof(szBuf));
	nRet = recv(remoteSocket,					// Connected client
		szBuf,							// Receive buffer
		sizeof(szBuf),					// Length of buffer
		0);								// Flags
	if (nRet == INVALID_SOCKET)
	{
		PRINTERROR("recv()");
		closesocket(listenSocket);
		closesocket(remoteSocket);
		return;
	}

	//
	// Display received data
	//
	szBuf[nRet] = 0;
	printf("\nData received: %s", szBuf);

	//
	// Send data back to the client
	//
	strcpy_s(szBuf, "From the Server");
	nRet = send(remoteSocket,				// Connected socket
		szBuf,						// Data buffer
		strlen(szBuf),				// Lenght of data
		0);							// Flags

//
// Close BOTH sockets before exiting
//
	closesocket(remoteSocket);
	closesocket(listenSocket);
	return;
}