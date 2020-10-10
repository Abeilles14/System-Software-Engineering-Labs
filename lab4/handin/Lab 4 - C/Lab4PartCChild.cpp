#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ctime>
#include <string>

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")

int main()
{
    std::cout << "Super cool server v2.0\n";

    // Configuration
    uint16_t thisPort = 24873;
    char ipAddress[13] = "192.168.1.12";
    std::string stringAddress = "192.168.1.12";

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


    // Server configuration
    char buffer[500];
    char outBuffer[500];
    uint16_t maxLength = 500;

    memset(buffer, 0, maxLength);
    memset(outBuffer, 0, maxLength);
    bool breakLoop = false;
    struct sockaddr_in sourceAddress;
    socklen_t sourceAddressLength = sizeof(sourceAddress);
    uint32_t storedNumber = 0;

    // Commands
    std::string quitString = "quit";
    std::string status = "status";
    std::string storeNumber = "store";
    std::string readNumber = "read";

    time_t initialTime = time(0);

    // Socket is now set up. Check port to receive messages
    // Main program loop
    std::cout << "Server started up successfully. Listening for messages...\n";
    for (;;) {
        if (breakLoop) {
            break;
        }
        ret = recvfrom(thisSocket, buffer, maxLength, 0, (sockaddr*)&sourceAddress, &sourceAddressLength);
        if (ret > 0) {
            std::cout << "Message received! It says: " << buffer << std::endl;

            // Quit condition
            for (uint8_t index = 0; index < quitString.length(); index++) {
                if (buffer[index] != quitString[index]) {
                    break;
                }

                if (index == quitString.length() - 1) {
                    std::cout << "Quit message received. Press any button to close the server......";
                    breakLoop = true;

                    std::string quitMessage = "Server shutting down";

                    for (uint8_t messageIndex = 0; messageIndex < quitMessage.length() + 1; messageIndex++) {
                        outBuffer[messageIndex] = quitMessage[messageIndex];
                    }
                }
            }

            // Status condition
            for (uint8_t index = 0; index < status.length(); index++) {
                if (buffer[index] != status[index]) {
                    break;
                }

                if (index == status.length() - 1) {
                    std::cout << "Displaying status...\n";
                    std::cout << "Server Ip Address: " << ipAddress << std::endl;
                    std::cout << "Server port: " << thisPort << std::endl;
                    std::cout << "Server uptime: " << time(0) - initialTime << " seconds\n";

                    std::string statusMessage = "Displaying status...\nServer Ip Address: " + stringAddress +
                        "\nServer port: " + std::to_string(thisPort) + "\nServer uptime: " + std::to_string(time(0) - initialTime)
                        + " seconds\n";

                    for (uint8_t messageIndex = 0; messageIndex < statusMessage.length() + 1; messageIndex++) {
                        outBuffer[messageIndex] = statusMessage[messageIndex];
                    }
                }
            }

            // Store number
            for (uint8_t index = 0; index < storeNumber.length(); index++) {
                if (buffer[index] != storeNumber[index]) {
                    break;
                }

                if (index == storeNumber.length() - 1) {
                    storedNumber = (uint32_t)atol(buffer + storeNumber.length());
                    std::cout << "Stored number: " << storedNumber << std::endl;
                    std::string outMessage = "Stored number: ";
                    outMessage += std::to_string(storedNumber);

                    for (uint8_t messageIndex = 0; messageIndex < outMessage.length() + 1; messageIndex++) {
                        outBuffer[messageIndex] = outMessage[messageIndex];
                    }
                }
            }

            // Read number
            for (uint8_t index = 0; index < readNumber.length(); index++) {
                if (buffer[index] != readNumber[index]) {
                    break;
                }

                if (index == readNumber.length() - 1) {
                    std::cout << "Stored number: " << storedNumber << std::endl;
                }

                std::string outMessage = "Stored number: ";
                outMessage += std::to_string(storedNumber);

                for (uint8_t messageIndex = 0; messageIndex < outMessage.length() + 1; messageIndex++) {
                    outBuffer[messageIndex] = outMessage[messageIndex];
                }
            }

            ret = sendto(thisSocket, (char*)outBuffer, maxLength, 0, (struct sockaddr*)&sourceAddress, sourceAddressLength);
        }
    }
    getchar();
    return 0;
}