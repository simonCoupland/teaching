#include "defs.h"
static HWND mainWindow;
static int i_windowWidth = 800;
static int i_windowHeight = 600;
static int i_bufferWidth = 0;
static int i_bufferHeight = 0;
static unsigned char * videoBuffer;
static BITMAPINFO bitMapInfo = { 0 };
static char * winName = "Connect 4";
static char * winTitle = "Connect 4 Game";

BOOL b_isRunning;
slotState playerColour;

void exitGameLoop()
{
	b_isRunning = FALSE;
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
	wc.lpszClassName = winName;

	if (!RegisterClass(&wc))
	{
		return -1;
	}

	DWORD windowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	RECT r;
	r.top = 0;
	r.left = 0;
	r.right = i_windowWidth;
	r.bottom = i_windowHeight;

	AdjustWindowRect(&r, windowStyle, FALSE);

	i_bufferWidth = r.right - r.left;
	i_bufferHeight = r.bottom - r.top;
	mainWindow = CreateWindowEx(
		0,
		winName,
		winTitle,
		windowStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		i_bufferWidth,
		i_bufferHeight,
		NULL,
		NULL,
		hInstance,
		0);

	videoBuffer = malloc(i_bufferWidth * i_bufferHeight * 4); // 4 Bytes per pixel

	bitMapInfo.bmiHeader.biSize = sizeof(bitMapInfo.bmiHeader);
	bitMapInfo.bmiHeader.biWidth = i_bufferWidth;
	bitMapInfo.bmiHeader.biHeight = -i_bufferHeight;
	bitMapInfo.bmiHeader.biPlanes = 1;
	bitMapInfo.bmiHeader.biBitCount = 8 * 4; // 4 bytes per pixel
	bitMapInfo.bmiHeader.biCompression = BI_RGB;

	ShowWindow(mainWindow, SW_SHOWDEFAULT);

	return 0;
}

void clearWindow(unsigned char red, unsigned char green, unsigned char blue)
{
	unsigned char colour = ((red << 16) | (green << 8) | blue);
	unsigned int* bufferWalker = (unsigned int*)videoBuffer;
	for (int i = 0; i < i_bufferHeight * i_bufferWidth; i++)
	{
		*bufferWalker = colour;
		bufferWalker++;
	}
}

void updateWindow(void)
{
	HDC dc = GetDC(mainWindow);
	StretchDIBits(dc,
		0, 0, i_windowWidth, i_windowHeight,
		0, 0, i_bufferWidth, i_bufferHeight,
		(void*)videoBuffer, (BITMAPINFO*)&bitMapInfo,
		DIB_RGB_COLORS, SRCCOPY);
	ReleaseDC(mainWindow, dc);
}


void drawImage32(int x, int y, int width, int height, unsigned char* source)
{
	unsigned char * dest = videoBuffer;

	// move to first pixel in the video buffer
	dest += (i_bufferWidth * 4 * y) + (x * 4);

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

		dest += i_bufferWidth * 4;
		bufferWalker = (unsigned int*)dest;
	}

}