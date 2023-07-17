#include <iostream>
#include <winsock2.h>
#include <chrono>
#include <cstdint>

#define PORT 1234
#define BUFFER_SIZE 1024

uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddress, clientAddress;
    int addressLength = sizeof(clientAddress);
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Set up the server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Failed to listen for connections." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Accept a connection from the client
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &addressLength);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to accept connection." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Read data from the client
    std::cout << timeSinceEpochMillisec() << std::endl;
    int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    std::cout << timeSinceEpochMillisec() << std::endl;

    // Display the received data
    std::cout << "Received data: " << buffer << std::endl;
    std::cout << timeSinceEpochMillisec() << std::endl;

    // Close the sockets
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
