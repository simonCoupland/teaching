#include "defs.h"

BOOL bIsRunning;
slotState playerColour;

void exitGameLoop()
{
	bIsRunning = FALSE;
	// Disconnect from the server
	sendMessage(-1); 
	closeConnection();
	// Clean up the video buffer
	free(s_pcVideoBuffer);
	s_pcVideoBuffer = NULL;
}

int buttonCheck(int x, int *position)
{
	if (x > 59)
	{
		if (x < 155) { *position = 0; return 1; }
		if (x < 250) { *position = 1; return 1; }
		if (x < 346) { *position = 2; return 1; }
		if (x < 442) { *position = 3; return 1; }
		if (x < 537) { *position = 4; return 1; }
		if (x < 635) { *position = 5; return 1; }
		if (x < 734) { *position = 6; return 1; }
	}
	return 0;
}

LRESULT CALLBACK mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	int position;
	int x;
	// Process user events
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		x = GET_X_LPARAM(lParam);
		// If a valid button has been hit
		if(buttonCheck(x, &position))
		{
			takeTurn(position);
		}		
		break;
	case WM_ACTIVATE:
		break;

	case WM_CREATE:
		break;

	case WM_DESTROY:
		exitGameLoop(0);
		break;
	default:
		result = DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return result;
}

int openWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCMdLine, int nShowCmd)
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = mainWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = s_pcWinName;

	if (!RegisterClass(&wc))
	{
		return -1;
	}

	DWORD windowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	RECT r;
	r.top = 0;
	r.left = 0;
	r.right = s_iWindowWidth;
	r.bottom = s_iWindowHeight;

	AdjustWindowRect(&r, windowStyle, FALSE);

	s_iBufferWidth = r.right - r.left;
	s_iBufferHeight = r.bottom - r.top;
	s_mainWindow = CreateWindowEx(
		0,
		s_pcWinName,
		s_pcWinTitle,
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		s_iBufferWidth,
		s_iBufferHeight,
		NULL,
		NULL,
		hInstance,
		0);

	s_pcVideoBuffer = malloc(s_iBufferWidth * s_iBufferHeight * 4); // 4 Bytes per pixel

	bitMapInfo.bmiHeader.biSize = sizeof(bitMapInfo.bmiHeader);
	bitMapInfo.bmiHeader.biWidth = s_iBufferWidth;
	bitMapInfo.bmiHeader.biHeight = -s_iBufferHeight;
	bitMapInfo.bmiHeader.biPlanes = 1;
	bitMapInfo.bmiHeader.biBitCount = 8 * 4; // 4 bytes per pixel
	bitMapInfo.bmiHeader.biCompression = BI_RGB;

	ShowWindow(s_mainWindow, SW_SHOWDEFAULT);

	return 0;
}

void clearWindow(unsigned char red, unsigned char green, unsigned char blue)
{
	unsigned char colour = ((red << 16) | (green << 8) | blue);
	unsigned int* bufferWalker = (unsigned int*)s_pcVideoBuffer;
	for (int i = 0; i < s_iBufferHeight * s_iBufferWidth; i++)
	{
		*bufferWalker = colour;
		bufferWalker++;
	}
}

void updateWindow(void)
{
	HDC dc = GetDC(s_mainWindow);
	StretchDIBits(dc,
		0, 0, s_iWindowWidth, s_iWindowHeight,
		0, 0, s_iBufferWidth, s_iBufferHeight,
		(void*)s_pcVideoBuffer, (BITMAPINFO*)&bitMapInfo,
		DIB_RGB_COLORS, SRCCOPY);
	ReleaseDC(s_mainWindow, dc);
}


void drawImage32(int x, int y, int width, int height, unsigned char* source)
{
	unsigned char * dest = s_pcVideoBuffer;

	// move to first pixel in the video buffer
	dest += (s_iBufferWidth * 4 * y) + (x * 4);

	unsigned int* bufferWalker = (unsigned int*)dest;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned char red = *source; source++;
			unsigned char green = *source; source++;
			unsigned char blue = *source; source++;
			unsigned int colour = ((red << 16) | (green << 8) | blue);

			// 65535 is tranparent 
			if (colour != 65535) {
				*bufferWalker = colour;
			}
			bufferWalker++;
			source++;
		}

		dest += s_iBufferWidth * 4;
		bufferWalker = (unsigned int*)dest;
	}

}
