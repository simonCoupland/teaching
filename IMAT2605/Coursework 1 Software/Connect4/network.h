#pragma once 

typedef enum { disconnected, connected } networkState;

int establishConnection(char * serverName);
int closeConnection(void);
int sendMessage(int position);
int checkForReply(int *position);
int waitForOther();

