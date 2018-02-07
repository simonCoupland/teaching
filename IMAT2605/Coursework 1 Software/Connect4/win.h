#pragma once

#include <Windows.h>


LRESULT CALLBACK mainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int openWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCMdLine, int nShowCmd);
void clearWindow(unsigned char red, unsigned char green, unsigned char blue);
void updateWindow(void);
void drawImage32(int X, int Y, int Width, int Height, unsigned char* Source);
void exitGameLoop();

// Extern always other files to access a global variable
// Id handles for loaded images
extern int boardId; 
extern int yellowId;
extern int redId;
extern int winnerId;
extern int loserId;