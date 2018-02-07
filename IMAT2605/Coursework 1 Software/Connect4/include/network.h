#pragma once 

typedef enum { disconnected, connected } networkState;

#define BUFFER_LENGTH 128
#define PORT "7777"

WSADATA wsaData; // WINSOCk data
SOCKET connection; // Connection to Server
networkState network; // Are we connected or not?

slotState playerColour;
slotState otherColour;


// Attempt to connect to the server
int establishConnection(char * serverName);
// Close connection to the server
int closeConnection(void);
// Send a message to the server
int sendMessage(int position);
// Check if server has replied
int checkForReply(int *position);
// wait for the the other player to join the game
int waitForOther();

