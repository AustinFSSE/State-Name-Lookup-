#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>

using namespace std;

int main(int argc, char* argv[]) {
    cout << "\n+- Client -+" << endl;
    cout << "\n+- Step 1 - Set up DLL -+" << endl;

    SOCKET clientSocket; // Variable to hold the client socket
    int port = 55555; // Port number to connect to
    WSADATA wsaData; // Structure to hold WinSock data
    int wsaerr; // Variable to hold error codes
    WORD wVersionRequested = MAKEWORD(2, 2); // Request WinSock version 2.2

    // Initialize WinSock
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    // Check if WinSock initialization was successful
    if (wsaerr != 0) {
        cout << " The Winsock dll not found!" << endl;
        return 0;
    }
    else {
        cout << "The winsock dll found!" << endl;
        cout << "The status: " << wsaData.szSystemStatus << endl;
    }

    cout << "\n+- Step 2. Create a client socket -+" << endl;

    clientSocket = INVALID_SOCKET; // Initialize clientSocket with an invalid value
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create a TCP socket

    // Check if the socket creation was successful
    if (clientSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup(); // Cleanup WinSock on error
        return 0;
    }
    else {
        cout << "socket() is OK!" << endl;
    }

    cout << "\n+- Step 3. Connect to the server using connect() -+" << endl;

    sockaddr_in clientService; // Structure to hold server address information
    clientService.sin_family = AF_INET; // Set address family to Internet
    InetPton(AF_INET, "127.0.0.1", &clientService.sin_addr.s_addr); // Connect to localhost
    clientService.sin_port = htons(port); // Connect to the specified port

    // Connect to the server
    if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        cout << "Client: connect() - Failed to connect." << endl;
        WSACleanup(); // Cleanup WinSock on error
        return 0;
    }
    else {
        cout << "Client: connect() is OK!" << endl;
    }

    cout << "\n+- Step 4. Send and receive data - recv(), send(), recvfrom(), sendto() -+" << endl;

    // Main loop to continuously send and receive data
    while (true) {
        string state_abbrev;
        cout << "Enter state abbreviation: ";
        cin >> state_abbrev;

        // Ensure the abbreviation is exactly 2 characters long
        if (state_abbrev.length() != 2) {
            cout << "Please enter a 2-character state abbreviation." << endl;
            continue;
        }

        // Send the state abbreviation to the server
        int n = send(clientSocket, state_abbrev.c_str(), 2, 0);

        // Check if there was an error sending data
        if (n == SOCKET_ERROR) {
            cerr << "Error writing to socket: " << WSAGetLastError() << endl;
            closesocket(clientSocket); // Close socket on error
            WSACleanup(); // Cleanup WinSock
            return 1;
        }

        char buffer[256]; // Buffer to store the response from the server

        // Receive the response from the server
        n = recv(clientSocket, buffer, 255, 0);

        // Check if there was an error receiving data
        if (n == SOCKET_ERROR) {
            cerr << "Error reading from socket: " << WSAGetLastError() << endl;
            closesocket(clientSocket); // Close socket on error
            WSACleanup(); // Cleanup WinSock
            return 1;
        }

        buffer[n] = '\0'; // Null-terminate the received string
        cout << "Server response: " << buffer << endl; // Display the response
    }

    closesocket(clientSocket); // Close the client socket
    WSACleanup(); // Cleanup WinSock

    return 0; // Return 0 to indicate successful execution
}
