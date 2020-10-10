#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ctime>

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")

#include "rt.h"

int main()
{
    std::cout << "Super cool client v2.0\n";
    // Configuration
    uint16_t thisPort = 24872;
    char ipAddress[13] = "192.168.1.12";
    int thisSocket = 0;
    struct sockaddr_in address;
    WSADATA  wsaData;

    std::cout << "Setting up windows socket functions...\n";
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
        std::cout << "Failed\n";
        return 0;
    }
    std::cout << "OK\n";

    // Create a UDP socket
    std::cout << "Creating UDP Socket...\n";
    thisSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (thisSocket < 0) {
        std::cout << "Failed\n";
        return 0;
    }
    std::cout << "OK\n";

    // Setup address
    memset((char*)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(thisPort);

    std::cout << "Binding Socket to port " << thisPort << "...\n";
    int ret = bind(thisSocket, (struct sockaddr*)&address, sizeof(address));
    if (ret != 0) {
        std::cout << "Failed\n";
        return 0;
    }
    std::cout << "OK\n";

    // Setup Server
    CProcess p1("Z:\\Eng\\cpen333\\Lab4PartC\\Debug\\Lab4PartCChild.exe",	// pathlist to child program executable				
        NORMAL_PRIORITY_CLASS,			// priority
        OWN_WINDOW,						// process has its own window					
        ACTIVE							// process is active immediately
    );

    char buffer[500];
    char inputBuffer[500];
    uint16_t bufferLength = 500;
    memset(buffer, 0, bufferLength);
    memset(inputBuffer, 0, bufferLength);

    struct sockaddr_in destinationAddress;
    int toAddrLen = sizeof(destinationAddress);

    bool breakLoop = false;

    std::string quitString = "quit";

    char destinationIp[13] = "192.168.1.12";
    uint16_t destinationPort = 24873;

    // Send a message
    cout << "Client started up successfully. Available commands include \"status\", \"store#\", \"read\", and \"quit\"" << std::endl;
    for (;;) {
        if (breakLoop) {
            break;
        }
        memset(buffer, 0, 500);
        std::cout << "\nSend the server a message: ";
        std::cin >> buffer;

        destinationAddress.sin_family = AF_INET;
        destinationAddress.sin_port = htons(destinationPort);

        inet_pton(AF_INET, destinationIp, &destinationAddress.sin_addr);

        ret = sendto(thisSocket, (char*)buffer, bufferLength, 0, (struct sockaddr*)&destinationAddress, toAddrLen);
        if (ret == bufferLength) {
            std::cout << "\nMessage sent!";

            // Check for response from server
            ret = recvfrom(thisSocket, inputBuffer, bufferLength, 0, (sockaddr*)&destinationAddress, &toAddrLen);
            if (ret > 0) {
                std::cout << "\nMessage received: " << inputBuffer << std::endl;
            }

            for (uint8_t index = 0; index < quitString.length(); index++) {
                if (buffer[index] != quitString[index]) {
                    break;
                }

                if (index == quitString.length() - 1) {
                    std::cout << "\nQuit message sent. Waiting for server to close...";
                    breakLoop = true;
                }
            }
        }

        Sleep(500);
    }
    p1.WaitForProcess();
    return 0;

}