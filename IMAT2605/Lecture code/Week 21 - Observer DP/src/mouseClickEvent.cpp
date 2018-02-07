#include "mouseClickEvent.h"

MouseClickEvent::MouseClickEvent()
{
	mouseButton = left;
	iXPos = -1;
	iYPos = -1;
}

MouseClickEvent::MouseClickEvent(MouseButton mb, int x, int y)
{
	mouseButton = mb;
	iXPos = x;
	iYPos = y;
}

MouseClickEvent::MouseButton MouseClickEvent::getButton() 
{
	return mouseButton;
}

int MouseClickEvent::getX() 
{
	return iXPos;
}

int MouseClickEvent::getY() 
{
	return iYPos;
}