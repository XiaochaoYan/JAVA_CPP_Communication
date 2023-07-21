#include <iostream>
#include <chrono>
#include <winsock2.h>
#include <cstring>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 1234
#define BUFFER_SIZE 1024
#define NUM_MESSAGES 1000000

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddress;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Set up the server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddress.sin_port = htons(SERVER_PORT);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to connect to the server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Prepare the message
    char message[BUFFER_SIZE];
    memset(message, 'A', BUFFER_SIZE);

    // Start the benchmark
    auto start = std::chrono::high_resolution_clock::now();

    // Send and receive messages to/from the server
    for (int i = 0; i < NUM_MESSAGES; i++) {
        send(clientSocket, message, BUFFER_SIZE, 0);
        recv(clientSocket, message, BUFFER_SIZE, 0);
    }

    // End the benchmark
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Calculate throughput and latency
    double throughput = NUM_MESSAGES * BUFFER_SIZE / (duration.count() * 1024 * 1024); // MB/s
    double latency = duration.count() / NUM_MESSAGES * 1000; // milliseconds

    std::cout << "Throughput: " << throughput << " MB/s" << std::endl;
    std::cout << "Latency: " << latency << " ms" << std::endl;

    // Close the socket and clean up Winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
