#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <unordered_map>

using namespace std;

// Map of state abbreviations to state names
unordered_map<string, string> state_names = {
    {"AL", "Alabama"}, {"AK", "Alaska"}, {"AZ", "Arizona"}, {"AR", "Arkansas"},
    {"CA", "California"}, {"CO", "Colorado"}, {"CT", "Connecticut"}, {"DE", "Delaware"},
    {"FL", "Florida"}, {"GA", "Georgia"}, {"HI", "Hawaii"}, {"ID", "Idaho"},
    {"IL", "Illinois"}, {"IN", "Indiana"}, {"IA", "Iowa"}, {"KS", "Kansas"},
    {"KY", "Kentucky"}, {"LA", "Louisiana"}, {"ME", "Maine"}, {"MD", "Maryland"},
    {"MA", "Massachusetts"}, {"MI", "Michigan"}, {"MN", "Minnesota"}, {"MS", "Mississippi"},
    {"MO", "Missouri"}, {"MT", "Montana"}, {"NE", "Nebraska"}, {"NV", "Nevada"},
    {"NH", "New Hampshire"}, {"NJ", "New Jersey"}, {"NM", "New Mexico"}, {"NY", "New York"},
    {"NC", "North Carolina"}, {"ND", "North Dakota"}, {"OH", "Ohio"}, {"OK", "Oklahoma"},
    {"OR", "Oregon"}, {"PA", "Pennsylvania"}, {"RI", "Rhode Island"}, {"SC", "South Carolina"},
    {"SD", "South Dakota"}, {"TN", "Tennessee"}, {"TX", "Texas"}, {"UT", "Utah"},
    {"VT", "Vermont"}, {"VA", "Virginia"}, {"WA", "Washington"}, {"WV", "West Virginia"},
    {"WI", "Wisconsin"}, {"WY", "Wyoming"}
};

// Function to handle client connections
void handle_client(SOCKET client_socket) {
    char buffer[3]; // Buffer to store state abbreviation from client

    // Continuously handle requests from the connected client
    while (true) {
        // Receive 2 bytes of data from the client (state abbreviation)
        int n = recv(client_socket, buffer, 2, 0);

        // Check if there was an error receiving data
        if (n == SOCKET_ERROR) {
            cerr << "Error reading from socket" << endl;
            closesocket(client_socket); // Close socket on error
            return;
        }

        // Check if the client has disconnected
        if (n == 0) {
            cout << "Client disconnected" << endl;
            closesocket(client_socket); // Close socket on client disconnect
            return;
        }

        buffer[2] = '\0'; // Null-terminate the received string to make it a valid C-string

        string abbrev(buffer); // Convert buffer to a C++ string
        string response;

        // Lookup the state name from the abbreviation
        if (state_names.find(abbrev) != state_names.end()) {
            response = state_names[abbrev];
        }
        else {
            response = "Invalid abbreviation"; // If abbreviation is invalid
        }

        // Send the response back to the client
        n = send(client_socket, response.c_str(), response.length(), 0);

        // Check if there was an error sending data
        if (n == SOCKET_ERROR) {
            cerr << "Error writing to socket" << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    cout << "\nStep 1 - Initialize WSA with WSAStartup()" << endl;

    SOCKET serverSocket; // Variable to hold the server socket
    int port = 55555; // Port number on which the server will listen
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

    cout << "\n+- Step 2. Create the server socket -+" << endl;

    serverSocket = INVALID_SOCKET; // Initialize serverSocket with an invalid value
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create a TCP socket

    // Check if the socket creation was successful
    if (serverSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        WSACleanup();
        return 0;
    }
    else {
        cout << "socket() is OK!" << endl;
    }

    cout << "\n+- Step 3. Bind the server socket -+" << endl;

    sockaddr_in service; // Structure to hold server address information
    service.sin_family = AF_INET; // Set address family to Internet
    InetPton(AF_INET, "127.0.0.1", &service.sin_addr.s_addr); // Bind to localhost
    service.sin_port = htons(port); // Bind to the specified port

    // Bind the socket to the address and port
    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed:" << WSAGetLastError() << endl;
        closesocket(serverSocket); // Close the socket on error
        WSACleanup(); // Cleanup WinSock
        return 1;
    }
    else {
        cout << "bind() is OK!" << endl;
    }

    cout << "\n+- Step 4. Initiate Listen() -+" << endl;

    // Start listening for incoming connection requests
    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        cout << "listen(): Error listening on socket" << WSAGetLastError() << endl;
    }
    else {
        cout << "listen() is OK, I'm waiting for connections..." << endl;
    }

    cout << "\n+- Step 5. Accept Connection from Client -+" << endl;

    sockaddr_in client_addr; // Structure to hold client address information
    int client_len = sizeof(client_addr); // Length of the client address structure

    // Main loop to continuously accept and handle client connections
    while (true) {
        // Accept a client connection
        SOCKET client_socket = accept(serverSocket, (SOCKADDR*)&client_addr, &client_len);

        // Check if the client connection was accepted successfully
        if (client_socket == INVALID_SOCKET) {
            cout << "accept failed:" << WSAGetLastError() << endl;
            WSACleanup(); // Cleanup WinSock on error
            return -1;
        }

        // Handle the client connection in a separate function
        handle_client(client_socket);
    }

    cout << "Accepted Connection" << endl;
    system("pause"); // Pause the system to keep the console open
    WSACleanup(); // Cleanup WinSock

    return 0; // Return 0 to indicate successful execution
}
