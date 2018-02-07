#pragma once

typedef enum {empty, red, yellow} slotState;
typedef enum {connecting, waitingForOther, playerTurn, otherTurn, gameOver} GameState;

extern slotState playerColour;
extern slotState otherColour;
slotState winningColour;
extern GameState gameState;

// Clear the board
void resetBoard(void);
// Take a turn at position
void takeTurn(int position);
// Opponent take a turn at position
void opponentTurn(int position);
// Check if the opponent has taken thier turn
void checkForTurn();
// Has either player won the game?
int winner(slotState);
// Has the game been drawn?
int drawn();
// Draw the board t the video buffer
void drawBoard(void);