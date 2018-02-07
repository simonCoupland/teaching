#include "defs.h"

BOOL b_isRunning;
image images[MAX_NUMBER_IMAGES];
slotState playerColour;
GameState gameState;

int boardId;
int yellowId;
int redId;
int winnerId;
int loserId;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Attempt to connect to a server
	gameState = connecting;

	// Retrieve server name from command line params
	if (lpCmdLine == "") exit(EXIT_FAILURE);

	char * serverName = NULL;
	char * paramWalker = lpCmdLine;
	int counter = 0;

	// Phew, what a loop condition!
	while (*paramWalker && (((*paramWalker >= '0') && (*paramWalker <= '9')) || (*paramWalker == '.')))
	{
		paramWalker++;
		counter++;
	}
	serverName = (char *)malloc(counter + 1);
	int r = strncpy_s(serverName, counter + 1, lpCmdLine,counter);

	// We've got the server name, lets try to establish a connection
	if (establishConnection(serverName) != 0)
	{
		// It's good to clean up!
		free(serverName);
		serverName = NULL;
		exit(EXIT_FAILURE);
	}

	// It's still good to clean up!
	free(serverName);
	serverName = NULL;

	// Set the mainloop test variable
	b_isRunning = TRUE;

	// Load the sprites
	boardId = readBMPFile("board.dib"); if (boardId == -1) exit(EXIT_FAILURE);
	yellowId = readBMPFile("yellow.dib"); if (yellowId == -1) exit(EXIT_FAILURE);
	redId = readBMPFile("red.dib"); if (redId == -1) exit(EXIT_FAILURE);
	winnerId = readBMPFile("winner.dib"); if (winnerId == -1) exit(EXIT_FAILURE);
	loserId = readBMPFile("loser.dib"); if (loserId == -1) exit(EXIT_FAILURE);
	

	// Reset the game board
	resetBoard();

	// Open the window
	if (openWindow(hInstance,hPrevInstance, lpCmdLine, nShowCmd) != 0)
	{
		exit(EXIT_FAILURE);
	}

	// Get ready for the game loop
	MSG callbackMsg;

	initTimer();

	float prevTime = timeElapsed();
	float currentTime = timeElapsed();
	float frameLength = 1.0f / 60.f;
	float timeAccumulated = 0.f;

	// Enter the game loop
	while (b_isRunning)
	{
		// Process any user events
		while (PeekMessage(&callbackMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&callbackMsg);
			DispatchMessage(&callbackMsg);
		}

		// Check frame time
		currentTime = timeElapsed();
		timeAccumulated += currentTime - prevTime;
		prevTime = currentTime;

		if (timeAccumulated > frameLength)
		{
			// Check if other player has played
			checkForTurn();

			// Run game frame
			clearWindow(0,0,0);

			// Draw the board
			drawBoard();

			// Draw the framebuffer to the window
			updateWindow();

			timeAccumulated -= frameLength;
		}
	}
}