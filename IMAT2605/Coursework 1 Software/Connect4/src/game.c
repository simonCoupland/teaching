#include "defs.h"

#define BOARD_HEIGHT 6
#define BOARD_WIDTH 7

slotState board[BOARD_WIDTH][BOARD_HEIGHT];
int aiBoardXs[BOARD_WIDTH][BOARD_HEIGHT];
int aiBoardYs[BOARD_WIDTH][BOARD_HEIGHT];
slotState playerColour;

int g_iBoardId;
int g_iYellowId;
int g_iRedId;
int g_iWinnerId;
int g_iLoserId;
int g_iDrawnId;

void resetBoard(void)
{
	aiBoardXs[0][0] = 80;  aiBoardYs[0][0] = 40;
	aiBoardXs[1][0] = 178; aiBoardYs[1][0] = 40;
	aiBoardXs[2][0] = 274; aiBoardYs[2][0] = 40;
	aiBoardXs[3][0] = 370; aiBoardYs[3][0] = 40;
	aiBoardXs[4][0] = 466; aiBoardYs[4][0] = 40;
	aiBoardXs[5][0] = 562; aiBoardYs[5][0] = 40;
	aiBoardXs[6][0] = 660; aiBoardYs[6][0] = 40;

	aiBoardXs[0][1] = 80;  aiBoardYs[0][1] = 130;
	aiBoardXs[1][1] = 178; aiBoardYs[1][1] = 130;
	aiBoardXs[2][1] = 274; aiBoardYs[2][1] = 130;
	aiBoardXs[3][1] = 370; aiBoardYs[3][1] = 130;
	aiBoardXs[4][1] = 466; aiBoardYs[4][1] = 130;
	aiBoardXs[5][1] = 562; aiBoardYs[5][1] = 130;
	aiBoardXs[6][1] = 660; aiBoardYs[6][1] = 130;

	aiBoardXs[0][2] = 80;  aiBoardYs[0][2] = 220;
	aiBoardXs[1][2] = 178; aiBoardYs[1][2] = 220;
	aiBoardXs[2][2] = 274; aiBoardYs[2][2] = 220;
	aiBoardXs[3][2] = 370; aiBoardYs[3][2] = 220;
	aiBoardXs[4][2] = 466; aiBoardYs[4][2] = 220;
	aiBoardXs[5][2] = 562; aiBoardYs[5][2] = 220;
	aiBoardXs[6][2] = 660; aiBoardYs[6][2] = 220;
										   
	aiBoardXs[0][3] = 80;  aiBoardYs[0][3] = 310;
	aiBoardXs[1][3] = 178; aiBoardYs[1][3] = 310;
	aiBoardXs[2][3] = 274; aiBoardYs[2][3] = 310;
	aiBoardXs[3][3] = 370; aiBoardYs[3][3] = 310;
	aiBoardXs[4][3] = 466; aiBoardYs[4][3] = 310;
	aiBoardXs[5][3] = 562; aiBoardYs[5][3] = 310;
	aiBoardXs[6][3] = 660; aiBoardYs[6][3] = 310;

	aiBoardXs[0][4] = 80;  aiBoardYs[0][4] = 400;
	aiBoardXs[1][4] = 178; aiBoardYs[1][4] = 400;
	aiBoardXs[2][4] = 274; aiBoardYs[2][4] = 400;
	aiBoardXs[3][4] = 370; aiBoardYs[3][4] = 400;
	aiBoardXs[4][4] = 466; aiBoardYs[4][4] = 400;
	aiBoardXs[5][4] = 562; aiBoardYs[5][4] = 400;
	aiBoardXs[6][4] = 660; aiBoardYs[6][4] = 400;

	aiBoardXs[0][5] = 80;  aiBoardYs[0][5] = 490;
	aiBoardXs[1][5] = 178; aiBoardYs[1][5] = 490;
	aiBoardXs[2][5] = 274; aiBoardYs[2][5] = 490;
	aiBoardXs[3][5] = 370; aiBoardYs[3][5] = 490;
	aiBoardXs[4][5] = 466; aiBoardYs[4][5] = 490;
	aiBoardXs[5][5] = 562; aiBoardYs[5][5] = 490;
	aiBoardXs[6][5] = 660; aiBoardYs[6][5] = 490;


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
			if (drawn())
			{
				sendMessage(-1); // Disconnect from the server
				gameState = gameOver;
				winningColour = empty;
			}
			else
			{
				// Other players turn
				gameState = otherTurn;
			}
		}
		else
		{
			sendMessage(-1); // Disconnect from the server
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
		if (drawn() == 1)
		{
			sendMessage(-1); // Disconnect from the server
			gameState = gameOver;
			winningColour = empty;
		}
		else
		{
			// Players turn
			gameState = playerTurn;
		}
	}
	else
	{
		sendMessage(-1); // Disconnect from the server
		gameState = gameOver;
		winningColour = otherColour;
	}
}

// Check used when wait for other player
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

// Draw the board to the videobuffer
void drawBoard(void)
{
	// Draw pieces
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			if (board[i][j] == yellow) drawImage32(aiBoardXs[i][j], aiBoardYs[i][j], images[g_iYellowId].m_width, images[g_iYellowId].m_height, images[g_iYellowId].m_data);
			if (board[i][j] == red) drawImage32(aiBoardXs[i][j], aiBoardYs[i][j], images[g_iRedId].m_width, images[g_iRedId].m_height, images[g_iRedId].m_data);
		}
	}

	// Draw over the top
	drawImage32(60, 25, images[g_iBoardId].m_width, images[g_iBoardId].m_height, images[g_iBoardId].m_data);

	// Check for a winner
	if (gameState == gameOver)
	{
		if (winningColour == playerColour)
		{
			// Draw you win!
			drawImage32(100, 100, images[g_iWinnerId].m_width, images[g_iWinnerId].m_height, images[g_iWinnerId].m_data);
		}
		else if (winningColour == otherColour)
		{
			// Draw you lose!
			drawImage32(100, 100, images[g_iLoserId].m_width, images[g_iLoserId].m_height, images[g_iLoserId].m_data);
		}
		else if (winningColour == empty)
		{
			// Draw you lose!
			drawImage32(100, 100, images[g_iDrawnId].m_width, images[g_iDrawnId].m_height, images[g_iDrawnId].m_data);
		}
	}
}


// Check if either player has won the game
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
		for (int j = 0; j + 3 < BOARD_HEIGHT; j++)
		{
			if (board[i][j] == colour && board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3]) return 1;
		}
	}
	// Check diagonal
	for (int i = 0; i < BOARD_WIDTH + 3; i++)
	{
		for (int j = 0; j + 3 < BOARD_HEIGHT; j++)
		{
			if (board[i][j] == colour && board[i][j] == board[i+1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3]) return 1;
			if (board[i + 3][j] == colour && colour == board[i + 2][j + 1] && colour == board[i + 1][j + 2] && colour == board[i][j + 3]) return 1;
		}
	}

	return -1;
}

// Check if the game is drawn
int drawn()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j + 3 < BOARD_HEIGHT; j++)
		{
			if (board[i][j] == empty) return 0;
		}
	}
	return 1;
}


