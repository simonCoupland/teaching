#ifndef MOUSECLICKEVENT_H
#define MOUSECLICKEVENT_H

class MouseClickEvent
{
public:
	enum MouseButton{left, right, wheel};
private:
	MouseButton mouseButton;
	int iXPos;
	int iYPos;
public:
	MouseClickEvent();
	MouseClickEvent(MouseButton mb, int x, int y);
	MouseButton getButton();
	int getX();
	int getY();
};

#endif