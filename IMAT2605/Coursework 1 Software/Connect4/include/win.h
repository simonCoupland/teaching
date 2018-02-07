#pragma once

#include <Windows.h>

// Callback function to handle all windows events - including mouse clicks
LRESULT CALLBACK mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
// Open a new Win23 window
int openWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCMdLine, int nShowCmd);
// Clear the video buffer with the 0-255 RGB colour in the parameters
void clearWindow(unsigned char red, unsigned char green, unsigned char blue);
// Write the video buffer to the screen
void updateWindow(void);
// Draw an image on the video buffer
void drawImage32(int X, int Y, int Width, int Height, unsigned char* Source);
// Stop the game
void exitGameLoop();
// Checks if a column in the game has been clicked
int buttonCheck(int x, int *position);

// Extern always other files to access a global variable
// Id handles for loaded images
extern int g_iBoardId; 
extern int g_iYellowId;
extern int g_iRedId;
extern int g_iWinnerId;
extern int g_iLoserId;
extern int g_iDrawnId;

static HWND s_mainWindow;
static int s_iWindowWidth = 800;
static int s_iWindowHeight = 600;
static int s_iBufferWidth = 0;
static int s_iBufferHeight = 0;
static unsigned char * s_pcVideoBuffer;  // Video buffer
static BITMAPINFO bitMapInfo = { 0 };
static char * s_pcWinName = "Connect 4";
static char * s_pcWinTitle = "Connect 4 Game";

