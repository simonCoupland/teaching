#include "defs.h"

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7

slotState board[BOARD_WIDTH][BOARD_HEIGHT];
int boardXs[BOARD_WIDTH][BOARD_HEIGHT];
int boardYs[BOARD_WIDTH][BOARD_HEIGHT];
slotState playerColour;

int boardId;
int yellowId;
int redId;

void resetBoard(void)
{
	boardXs[0][0] = 80;  boardYs[0][0] = 40;
	boardXs[1][0] = 178; boardYs[1][0] = 40;
	boardXs[2][0] = 274; boardYs[2][0] = 40;
	boardXs[3][0] = 370; boardYs[3][0] = 40;
	boardXs[4][0] = 466; boardYs[4][0] = 40;
	boardXs[5][0] = 562; boardYs[5][0] = 40;
	boardXs[6][0] = 660; boardYs[6][0] = 40;

	boardXs[0][1] = 80;  boardYs[0][1] = 130;
	boardXs[1][1] = 178; boardYs[1][1] = 130;
	boardXs[2][1] = 274; boardYs[2][1] = 130;
	boardXs[3][1] = 370; boardYs[3][1] = 130;
	boardXs[4][1] = 466; boardYs[4][1] = 130;
	boardXs[5][1] = 562; boardYs[5][1] = 130;
	boardXs[6][1] = 660; boardYs[6][1] = 130;

	boardXs[0][2] = 80;  boardYs[0][2] = 220;
	boardXs[1][2] = 178; boardYs[1][2] = 220;
	boardXs[2][2] = 274; boardYs[2][2] = 220;
	boardXs[3][2] = 370; boardYs[3][2] = 220;
	boardXs[4][2] = 466; boardYs[4][2] = 220;
	boardXs[5][2] = 562; boardYs[5][2] = 220;
	boardXs[6][2] = 660; boardYs[6][2] = 220;
										   
	boardXs[0][3] = 80;  boardYs[0][3] = 310;
	boardXs[1][3] = 178; boardYs[1][3] = 310;
	boardXs[2][3] = 274; boardYs[2][3] = 310;
	boardXs[3][3] = 370; boardYs[3][3] = 310;
	boardXs[4][3] = 466; boardYs[4][3] = 310;
	boardXs[5][3] = 562; boardYs[5][3] = 310;
	boardXs[6][3] = 660; boardYs[6][3] = 310;

	boardXs[0][4] = 80;  boardYs[0][4] = 400;
	boardXs[1][4] = 178; boardYs[1][4] = 400;
	boardXs[2][4] = 274; boardYs[2][4] = 400;
	boardXs[3][4] = 370; boardYs[3][4] = 400;
	boardXs[4][4] = 466; boardYs[4][4] = 400;
	boardXs[5][4] = 562; boardYs[5][4] = 400;
	boardXs[6][4] = 660; boardYs[6][4] = 400;

	boardXs[0][5] = 80;  boardYs[0][5] = 490;
	boardXs[1][5] = 178; boardYs[1][5] = 490;
	boardXs[2][5] = 274; boardYs[2][5] = 490;
	boardXs[3][5] = 370; boardYs[3][5] = 490;
	boardXs[4][5] = 466; boardYs[4][5] = 490;
	boardXs[5][5] = 562; boardYs[5][5] = 490;
	boardXs[6][5] = 660; boardYs[6][5] = 490;


	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			board[i][j] = empty;
		}
	}
}

void placePiece(int position, slotState colour)
{
	if (position < 0 || position >= BOARD_WIDTH) return;

	for (int j = BOARD_HEIGHT - 1; j >= 0; j--)
	{
		if (board[position][j] == empty)
		{
			board[position][j] = colour;
			return;
		}
	}
}

void takeTurn(int position)
{
	if (gameState == playerTurn)
	{
		// Place the piece
		placePiece(position, playerColour);

		// Send a message to the server
		if (sendMessage(position) != 0)
		{
			exitGameLoop();
		}

		// Check for a winner
		if (winner(playerColour) == -1)
		{
			// Other players turn
			gameState = otherTurn;
		}
		else
		{
			gameState = gameOver;
			winningColour = playerColour;
		}
	}
}

void opponentTurn(int position)
{
	// Place the piece
	placePiece(position, otherColour);

	// Check for a winner
	if (winner(otherColour) == -1)
	{
		// Players turn
		gameState = playerTurn;
	}
	else
	{
		gameState = gameOver;
		winningColour = otherColour;
	}
}

void checkForTurn()
{
	if (gameState == waitingForOther)
	{
		if (waitForOther() == 0)
		{
			gameState = playerTurn;
		}
	}

	if (gameState == otherTurn)
	{
		int position;

		if (checkForReply(&position) == 0)
		{
			opponentTurn(position);
		}
	}
}

void drawBoard(void)
{
	// Draw pieces
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			if (board[i][j] == yellow) drawImage32(boardXs[i][j], boardYs[i][j], images[yellowId].width, images[yellowId].height, images[yellowId].data);
			if (board[i][j] == red) drawImage32(boardXs[i][j], boardYs[i][j], images[redId].width, images[redId].height, images[redId].data);
		}
	}

	// Draw over the top
	drawImage32(60, 25, images[boardId].width, images[boardId].height, images[boardId].data);

	// Check for a winner
	if (gameState == gameOver)
	{
		if (winningColour == playerColour)
		{
			// Draw you win!
			drawImage32(100, 100, images[winnerId].width, images[winnerId].height, images[winnerId].data);
		}

		if (winningColour == otherColour)
		{
			// Draw you lose!
			drawImage32(100, 100, images[loserId].width, images[loserId].height, images[loserId].data);
		}
	}
}


int winner(slotState colour)
{
	// Check horizontal
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j + 3 < BOARD_WIDTH; j++)
		{
			if (board[j][i] == colour && board[j][i] == board[j + 1][i] && board[j + 1][i] == board[j + 2][i] && board[j + 2][i] == board[j + 3][i]) return 1;
		}
	}

	// Check vertical
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j + 3< BOARD_HEIGHT; j++)
		{
			if (board[i][j] == colour && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3]) return 1;
		}
	}
	return -1;
}



