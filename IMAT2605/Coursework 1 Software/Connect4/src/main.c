#include "defs.h"

BOOL bIsRunning;
image images[MAX_NUMBER_IMAGES];
slotState playerColour;
GameState gameState;

int g_iBoardId;
int g_iYellowId;
int g_iRedId;
int g_iWinnerId;
int g_iLoserId;
int g_iDrawnId;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Attempt to connect to a server
	gameState = connecting;

	// Retrieve server name from command line params
	if (lpCmdLine == "") exit(EXIT_FAILURE);

	char * pcServerName = NULL;
	char * pcParamWalker = lpCmdLine;
	int iCounter = 0;

	// Phew, what a loop condition!
	while (*pcParamWalker && (((*pcParamWalker >= '0') && (*pcParamWalker <= '9')) || (*pcParamWalker == '.')))
	{
		pcParamWalker++;
		iCounter++;
	}
	pcServerName = (char *)malloc(iCounter + 1);
	int r = strncpy_s(pcServerName, iCounter + 1, lpCmdLine,iCounter);

	// We've got the server name, lets try to establish a connection
	if (establishConnection(pcServerName) != 0)
	{
		// It's good to clean up!
		free(pcServerName);
		pcServerName = NULL;
		exit(EXIT_FAILURE);
	}

	// It's still good to clean up!
	free(pcServerName);
	pcServerName = NULL;

	// Set the mainloop test variable
	bIsRunning = TRUE;

	// Load the sprites
	g_iBoardId = readBMPFile("./assets/board.dib"); if (g_iBoardId == -1) exit(EXIT_FAILURE);
	g_iYellowId = readBMPFile("./assets/yellow.dib"); if (g_iYellowId == -1) exit(EXIT_FAILURE);
	g_iRedId = readBMPFile("./assets/red.dib"); if (g_iRedId == -1) exit(EXIT_FAILURE);
	g_iWinnerId = readBMPFile("./assets/winner.dib"); if (g_iWinnerId == -1) exit(EXIT_FAILURE);
	g_iLoserId = readBMPFile("./assets/loser.dib"); if (g_iLoserId == -1) exit(EXIT_FAILURE);
	g_iDrawnId = readBMPFile("./assets/drawn.dib"); if (g_iDrawnId == -1) exit(EXIT_FAILURE);

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

	float fPrevTime = timeElapsed();
	float fCurrentTime = timeElapsed();
	float fFrameLength = 1.0f / 60.f;
	float fTimeAccumulated = 0.f;

	// Enter the game loop
	while (bIsRunning)
	{
		// Process any user events
		while (PeekMessage(&callbackMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&callbackMsg);
			DispatchMessage(&callbackMsg);
		}

		// Check frame time
		fCurrentTime = timeElapsed();
		fTimeAccumulated += fCurrentTime - fPrevTime;
		fPrevTime = fCurrentTime;

		if (fTimeAccumulated > fFrameLength && bIsRunning)
		{
			// Check if other player has played
			checkForTurn();

			// Run game frame
			clearWindow(0,0,0);

			// Draw the board
			drawBoard();

			// Draw the framebuffer to the window
			updateWindow();

			// Remove frame time from accumlated time (gives a steadier timestep)
			fTimeAccumulated -= fFrameLength;
		}
	}
}