# State Name Lookup Server and Client
This project consists of a server and a client application written in C++ that use WinSock for socket communication. The server receives state abbreviations from the client and responds with the corresponding state name. If the abbreviation is invalid, the server returns an error message.

Features
Server: Listens for incoming connections, handles multiple client connections, and processes state abbreviation lookup requests.
Client: Connects to the server, sends state abbreviations, and receives state names or error messages.
Prerequisites
Windows OS
Microsoft Visual Studio (or any C++ compiler that supports WinSock)
Basic knowledge of C++ and socket programming
Getting Started
Setting up the Project
Clone the repository or download the source files server.cpp and client.cpp.

Open the project in your IDE (e.g., Visual Studio).

Ensure WinSock is included in your project settings.

Compiling the Code
Open Visual Studio and create a new project for the server.

Add server.cpp to the project.
Build the project to generate the executable.
Create another project for the client.

Add client.cpp to the project.
Build the project to generate the executable.
Running the Server
Run the server executable.
The server will initialize WinSock, create a socket, bind it to 127.0.0.1:55555, and start listening for incoming connections.
Running the Client
Run the client executable.
The client will initialize WinSock, create a socket, and connect to the server at 127.0.0.1:55555.
The client will prompt you to enter a state abbreviation.
How it Works
Server (server.cpp)
Initialize WinSock: The server initializes the WinSock library using WSAStartup().
Create a Socket: A TCP socket is created using socket().
Bind the Socket: The socket is bound to the localhost address and port 55555 using bind().
Listen for Connections: The server listens for incoming connections using listen().
Accept Connections: The server accepts client connections using accept().
Handle Client Requests: In a loop, the server receives state abbreviations from the client, looks up the state name, and sends the response back to the client.
Client (client.cpp)
Initialize WinSock: The client initializes the WinSock library using WSAStartup().
Create a Socket: A TCP socket is created using socket().
Connect to Server: The client connects to the server at 127.0.0.1:55555 using connect().
Send and Receive Data: In a loop, the client prompts the user for a state abbreviation, sends it to the server, and prints the response received from the server.
