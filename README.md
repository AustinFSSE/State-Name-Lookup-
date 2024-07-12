TCP/IP Client-Server Application in C++
This repository contains a TCP/IP client-server application implemented in C++. The project demonstrates fundamental concepts of socket programming, data transmission over TCP/IP protocols, and error handling strategies. Whether you're new to network programming or looking to deepen your understanding, this project serves as a practical guide.

Table of Contents
Features
Prerequisites
Installation
Usage
Implementation Details
Contributing
License
Features
Client-Server Interaction: Establishes a connection between a client and server using TCP/IP sockets.
Data Transmission: Sends and receives data between client and server, demonstrating bidirectional communication.
Error Handling: Implements robust error handling techniques for socket operations.
Simple Protocol: Utilizes a simple protocol for sending and receiving state abbreviations and returning corresponding state names.
Prerequisites
Before running the application, ensure you have the following installed:

C++ compiler compatible with C++11 standards
Windows environment for Winsock library (winsock2.h, WS2tcpip.h)
Installation
Clone the repository:

bash
Copy code
git clone https://github.com/your-username/tcp-ip-client-server.git
cd tcp-ip-client-server
Compile the server and client applications using your preferred C++ compiler.

bash
Copy code
g++ server.cpp -o server.exe -lws2_32
g++ client.cpp -o client.exe -lws2_32
Usage
Start the Server:

bash
Copy code
./server.exe
The server initializes and waits for incoming connections on port 55555.

Run the Client:

bash
Copy code
./client.exe
The client prompts you to enter a state abbreviation (e.g., "CA" for California). It sends the abbreviation to the server, which responds with the corresponding state name.

Interact with the Application:

Enter state abbreviations on the client side to retrieve state names from the server.
View server console logs for connection status and data exchange messages.
Implementation Details
Server (server.cpp)
The server application initializes Winsock, creates a TCP/IP socket, binds it to a specified IP address and port, listens for incoming connections, and handles client requests. Key functionalities include:

Socket setup and error checking (socket(), bind(), listen()).
Accepting incoming client connections (accept()).
Handling client requests (recv(), send()).
Data processing and response generation based on predefined state abbreviations.
Client (client.cpp)
The client application initializes Winsock, creates a TCP/IP socket, connects to the server, sends user input (state abbreviations), receives server responses (state names), and displays them to the user. Key functionalities include:

Socket setup and error checking (socket(), connect()).
Sending user input to the server (send()).
Receiving server responses (recv()).
Displaying state names retrieved from the server.
Contributing
Contributions are welcome! If you have suggestions for improvements, bug fixes, or additional features, feel free to open an issue or create a pull request.

License
This project is licensed under the MIT License - see the LICENSE file for details.
