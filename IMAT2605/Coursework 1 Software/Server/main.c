#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_LENGTH 128
#define PORT "7777"

int main(void)
{
	BOOL redConnected = FALSE;
	BOOL yellowConnected = FALSE;

	int result;
	WSADATA wsaData;

	SOCKET serverSocket = INVALID_SOCKET;
	SOCKET redClientSocket = INVALID_SOCKET;
	SOCKET yellowClientSocket = INVALID_SOCKET;


	char recvbuf[BUFFER_LENGTH];
	int recvbuflen = BUFFER_LENGTH;
	char sendbuf[BUFFER_LENGTH];

	// Init winsock2
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		printf("Error: %d\n", result);
		return 1;
	}

	struct addrinfo *addr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	result = getaddrinfo(NULL, PORT, &hints, &addr);
	if (result != 0) {
		printf("Error: %d\n", result);
		WSACleanup();
		return 1;
	}
	
	// Create a socket for connecting to server
	serverSocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if (serverSocket == INVALID_SOCKET) {
		printf("Error: %ld\n", WSAGetLastError());
		freeaddrinfo(addr);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	result = bind(serverSocket, addr->ai_addr, (int)addr->ai_addrlen);
	if (result == SOCKET_ERROR) {
		printf("Error: %d\n", WSAGetLastError());
		freeaddrinfo(addr);
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(addr);

	result = listen(serverSocket, SOMAXCONN);
	if (result == SOCKET_ERROR) {
		printf("Error: %d\n", WSAGetLastError());
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}

	printf_s("Connect 4 Server\n----------------\nListening on port %s\n\n", PORT);

	// Accept the red client socket
	redClientSocket = accept(serverSocket, NULL, NULL);
	if (redClientSocket == INVALID_SOCKET) {
		printf("Error: %d\n", WSAGetLastError());
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	redConnected = TRUE;
	printf_s("Red client connected\nWaiting for yellow.....\n\n");

	result = recv(redClientSocket, recvbuf, recvbuflen, 0);
	if (result > 0) {
		printf("Bytes received from red client: %d\n", result);

		// Reply to client
		result = send(redClientSocket, "R", 2, 0);
		if (result == SOCKET_ERROR) {
			printf("Error: %d\n", WSAGetLastError());
			closesocket(redClientSocket);
			closesocket(yellowClientSocket);
			WSACleanup();
			return 1;
		}
		printf("Bytes sent to red client: %d\n", result);
	}
	else if (result == 0)
		printf("Connection closing...\n");
	else  {
		printf("Error: %d\n", WSAGetLastError());
		closesocket(redClientSocket);
		closesocket(yellowClientSocket);
		WSACleanup();
		return 1;
	}

	
	// Accept the yellow client socket
	yellowClientSocket = accept(serverSocket, NULL, NULL);
	if (yellowClientSocket == INVALID_SOCKET) {
		printf("Error: %d\n", WSAGetLastError());
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	yellowConnected = TRUE;
	printf_s("Yellow client connected\nStart game.....\n\n");


	result = recv(yellowClientSocket, recvbuf, recvbuflen, 0);
	if (result > 0) {
		printf("Bytes received from yellow client: %d\n", result);

		// Reply to the client
		result = send(yellowClientSocket, "Y", 2, 0);
		if (result == SOCKET_ERROR) {
			printf("Error: %d\n", WSAGetLastError());
			closesocket(redClientSocket);
			closesocket(yellowClientSocket);
			WSACleanup();
			return 1;
		}
		printf("Bytes sent to Yellow client: %d\n", result);
	}
	else if (result == 0)
		printf("Connection closing...\n");
	else  {
		printf("Error: %d\n", WSAGetLastError());
		closesocket(redClientSocket);
		closesocket(yellowClientSocket);
		WSACleanup();
		return 1;
	}

	// Close the server socket - it's no longer needed
	closesocket(serverSocket);

	
	// Send start message out to red client
	result = send(redClientSocket, "GO", 3, 0);
	if (result == SOCKET_ERROR) {
			printf("Error: %d\n", WSAGetLastError());
			closesocket(redClientSocket);
			closesocket(yellowClientSocket);
			WSACleanup();
			return 1;
	}
	else if (result == 0)
	{
		printf("Connection closing...\n");
		closesocket(redClientSocket);
		closesocket(yellowClientSocket);
		WSACleanup();
		return 1;
	}



	printf("\n\nStarting game: \n\n");

	// Poll both servers gathering any messages
	int id = 0;
	int position = 0;
	
	do {
		// Poll red client
		result = recv(redClientSocket, recvbuf, recvbuflen, 0);
		if (result > 0) {
			printf("Bytes received from red client: %d\n", result);
			sscanf_s(recvbuf, "Con4:%d:%d", &id, &position);
			sprintf_s(sendbuf, BUFFER_LENGTH, "%d", position);
			if (position == -1)
			{
				redConnected = FALSE;
				printf("Red client disconnected\n");
			}
			else
			{
				do
				{
					result = send(yellowClientSocket, sendbuf, strlen(sendbuf), 0);
					if (result == SOCKET_ERROR) {
						printf("Error: %d\n", WSAGetLastError());
						closesocket(redClientSocket);
						closesocket(yellowClientSocket);
						WSACleanup();
						return 1;
					}
				} while (result < 1);
				printf("Bytes sent to yellow client: %d\n", result);
			}
		}

		// Poll yellow client
		result = recv(yellowClientSocket, recvbuf, recvbuflen, 0);
		if (result > 0) {
			printf("Bytes received from yellow client: %d\n", result);
			sscanf_s(recvbuf, "Con4:%d:%d", &id, &position);
			sprintf_s(sendbuf, BUFFER_LENGTH, "%d", position);
			if (position == -1)
			{
				yellowConnected = FALSE;
				printf("Red client disconnected\n");
			}
			else
			{
				do
				{
					result = send(redClientSocket, sendbuf, strlen(sendbuf), 0);
					if (result == SOCKET_ERROR) {
						printf("Error: %d\n", WSAGetLastError());
						closesocket(redClientSocket);
						closesocket(yellowClientSocket);
						WSACleanup();
						return 1;
					}
				} while (result < 1);
				printf("Bytes sent to red client: %d\n", result);
			}
		}
		
		
	} while (redConnected && yellowConnected);

	// shutdown the connections to both clients 
	result = shutdown(redClientSocket, SD_SEND);
	if (result == SOCKET_ERROR) {
		printf("error: %d\n", WSAGetLastError());
		closesocket(redClientSocket);
		WSACleanup();
		return 1;
	}
 
	result = shutdown(yellowClientSocket, SD_SEND);
	if (result == SOCKET_ERROR) {
		printf("error: %d\n", WSAGetLastError());
		closesocket(yellowClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(redClientSocket);
	closesocket(yellowClientSocket);

	WSACleanup();

	printf("All done closing down\n\nBye bye!");

	return 0;
}