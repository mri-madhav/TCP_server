#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {

    // Initialize Winsock
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        cout << "WSAStartup failed!" << endl;
        return 1;
    }

    //Socket Creation
    SOCKET serverSocket = INVALID_SOCKET;

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket() is OK!" << endl;
    }

    // Bind to Port 8080
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(8080);

    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }
    else {
        cout << "bind() is OK!" << endl;
    }

    //  Listen for Client
    if (listen(serverSocket, 1) == SOCKET_ERROR)
        cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
    else
        cout << "listen() is OK, I'm waiting for connections..." << endl;

    // Accept Client
    SOCKET acceptSocket;

    acceptSocket = accept(serverSocket, NULL, NULL);

    if (acceptSocket == INVALID_SOCKET) {
        cout << "accept failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return -1;
    }
    else {
        cout << "accept() is OK!" << endl;
    }

    // Receive Message
    char buffer[1024];

    int bytesRecv = recv(acceptSocket, buffer, 1024, 0);

    if (bytesRecv > 0) {
        buffer[bytesRecv] = '\0';
        cout << "Message received: " << buffer << endl;
    }
    else {
        cout << "recv() failed: " << WSAGetLastError() << endl;
    }

    // Cleanup
    closesocket(acceptSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
