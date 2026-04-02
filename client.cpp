#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {

    // 🔹 0. Initialize Winsock
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        cout << "WSAStartup failed!" << endl;
        return 1;
    }

    // 🔹 1. Create Socket
    SOCKET clientSocket = INVALID_SOCKET;

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET) {
        cout << "socket() failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket() is OK!" << endl;
    }

    // 🔹 2. Setup Server Address (localhost:8080)
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &serverAddr.sin_addr.s_addr);
    serverAddr.sin_port = htons(8080);

    // 🔹 3. Connect
    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "connect() failed: " << WSAGetLastError() << endl;
        closesocket(clientSocket);
        WSACleanup();
        return 0;
    }
    else {
        cout << "connect() is OK!" << endl;
    }

    // 🔹 4. Send Message
    const char* msg = "Hello Server";

    int bytesSent = send(clientSocket, msg, strlen(msg), 0);

    if (bytesSent == SOCKET_ERROR) {
        cout << "send() failed: " << WSAGetLastError() << endl;
    }
    else {
        cout << "Message sent: " << msg << endl;
    }

    // 🔹 5. Cleanup
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}