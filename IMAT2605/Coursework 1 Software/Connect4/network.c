#include "defs.h"

#define BUFFER_LENGTH 128
#define PORT "7777"

WSADATA wsaData;
SOCKET connection;
networkState network;

slotState playerColour;
slotState otherColour;

int handleCommsError(void)
{
	WSACleanup();
	if (network == connected)
	{
		closesocket(connection);
		connection = INVALID_SOCKET;
		network = disconnected;
	}
	return -1;
}
int establishConnection(char * serverName)
{
	struct addrinfo *addr = NULL;
	struct addrinfo hints;
	char sendbuf[BUFFER_LENGTH];
	char recvbuf[BUFFER_LENGTH];
	int recvbuflen = BUFFER_LENGTH;
	int result;


	// Initialize Winsock
	network = disconnected;
	connection = INVALID_SOCKET;
	result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) return -1;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	result = getaddrinfo(serverName, PORT, &hints, &addr);
	if (result != 0) return handleCommsError();

	// Create a SOCKET for connecting to server
	connection = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if (connection == INVALID_SOCKET) return handleCommsError();

	// Connect to server.
	result = connect(connection, addr->ai_addr, (int)addr->ai_addrlen);
	if (result == SOCKET_ERROR) {
		closesocket(connection);
		connection = INVALID_SOCKET;
		// it's good to clean up
		freeaddrinfo(addr);
		addr = NULL;
	}

	// it's still good to clean up
	freeaddrinfo(addr);
	addr = NULL;

	if (connection == INVALID_SOCKET) return handleCommsError();


	// We are now connected to the server
	network = connected;

	// Send an initial buffer
	sprintf_s(sendbuf, BUFFER_LENGTH, "Con4:-1:-1");
	result = send(connection, sendbuf, (int)strlen(sendbuf), 0);
	if (result == SOCKET_ERROR) return handleCommsError();

	// Receive back colour for the player
	result = recv(connection, recvbuf, recvbuflen, 0);

	// Check we got 2 bytes
	if (result != 2) { return handleCommsError(); }

	// Set player and other colour and game state
	if (recvbuf[0] == 'R')
	{
		playerColour = red;
		otherColour = yellow;
		gameState = waitingForOther;
	}
	else if (recvbuf[0] == 'Y')
	{
		playerColour = yellow;
		otherColour = red;
		gameState = otherTurn;
	}
	else
	{
		return handleCommsError();
	}

	// Make connection non-blocking
	unsigned long iMode = 1;
	ioctlsocket(connection, FIONBIO, &iMode);

	return 0;
}

int closeConnection(void)
{
	int result;
	char recvbuf[BUFFER_LENGTH];
	int recvbuflen = BUFFER_LENGTH;
	// Receive until all wait bytes have been read
	do {
		result = recv(connection, recvbuf, recvbuflen, 0);
	} while (result > 0);

	// cleanup
	closesocket(connection);
	WSACleanup();

	return 0;
}

int sendMessage(int position)
{
	int result;
	char sendbuf[BUFFER_LENGTH];

	sprintf_s(sendbuf, BUFFER_LENGTH, "Con4:%d:%d", playerColour, position);
	result = send(connection, sendbuf, (int)strlen(sendbuf), 0);

	if (result == SOCKET_ERROR) return handleCommsError();

	gameState = otherTurn;
	return 0;
}

int checkForReply(int *position)
{
	char recvbuf[BUFFER_LENGTH];
	int recvbuflen = BUFFER_LENGTH;
	int result;

	result = recv(connection, recvbuf, recvbuflen, 0);

	if (result > 0)
	{
		sscanf_s(recvbuf, "%d", position);
		if (*position >= 0 && *position < 7) return 0;
	}
	return -1;
}

int waitForOther()
{
	char recvbuf[BUFFER_LENGTH];
	int recvbuflen = BUFFER_LENGTH;
	int result;

	result = recv(connection, recvbuf, recvbuflen, 0);
	if (result == 3)
	{
		if (recvbuf[0] == 'G' && recvbuf[1] == 'O')
		{
			return 0;
		}
		else
		{
			return handleCommsError();
		}
	}
	return -1;
}