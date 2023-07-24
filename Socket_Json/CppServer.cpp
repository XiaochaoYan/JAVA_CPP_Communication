#include <iostream>
#include <string>
#include <WinSock2.h>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#pragma comment(lib, "ws2_32.lib")

void processJSONData(const rapidjson::Value& jsonData) {
    if (jsonData.IsObject()) {
        if (jsonData.HasMember("value") && jsonData.HasMember("message")) {
            int value = jsonData["value"].GetInt();
            std::string message = jsonData["message"].GetString();
            std::cout << "Received JSON data:" << std::endl;
            std::cout << "Value: " << value << std::endl;
            std::cout << "Message: " << message << std::endl;
        } else {
            std::cerr << "Invalid JSON data format." << std::endl;
        }
    } else {
        std::cerr << "Invalid JSON data." << std::endl;
    }
}

std::string createJSONResponse(const std::string& message) {
    rapidjson::Document response;
    response.SetObject();
    rapidjson::Document::AllocatorType& allocator = response.GetAllocator();

    response.AddMember("message", rapidjson::Value(message.c_str(), allocator).Move(), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    response.Accept(writer);

    return buffer.GetString();
}

int main() {
    int serverPort = 1234;

    // Initialize WinSock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize WinSock." << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket." << std::endl;
        WSACleanup();
        return 1;
    }

    // Bind the socket to an address and port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(serverPort);
    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Error binding socket." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Error listening for connections." << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port " << serverPort << std::endl;

    while (true) {
        // Accept a new connection
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Error accepting connection." << std::endl;
            continue;
        }

        // Read data from the client
        char buffer[1024];
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << "Error reading data from client." << std::endl;
            closesocket(clientSocket);
            continue;
        }

        std::string jsonData(buffer, bytesRead);

        // Parse JSON data
        rapidjson::Document doc;
        if (doc.Parse(jsonData.c_str()).HasParseError()) {
            std::cerr << "Failed to parse JSON data." << std::endl;
            closesocket(clientSocket);
            continue;
        }

        // Process JSON data
        processJSONData(doc);

        std::string jsonResponse = createJSONResponse("Data received successfully!");

        // Send the JSON response back to the client
        int bytesSent = send(clientSocket, jsonResponse.c_str(), static_cast<int>(jsonResponse.size()), 0);
        if (bytesSent <= 0) {
            std::cerr << "Error sending response to the client." << std::endl;
        }

        // Close the client socket
        closesocket(clientSocket);
    }

    // Close the server socket and cleanup WinSock
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
