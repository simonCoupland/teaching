#pragma once

typedef enum {empty, red, yellow} slotState;
typedef enum {connecting, waitingForOther, playerTurn, otherTurn, gameOver} GameState;

extern slotState playerColour;
extern slotState otherColour;
slotState winningColour;
extern GameState gameState;

void resetBoard(void);
void takeTurn(int position);
void opponentTurn(int position);
void checkForTurn();
int winner(slotState);
void drawBoard(void);