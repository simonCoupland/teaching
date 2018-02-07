#ifndef MOUSECLICKOBSERVER_H
#define MOUSECLICKOBSERVER_H

#include "MouseClickEvent.h"
#include <string>
#include <iostream>

using namespace std;

class MouseClickObserver
{
private:
	string a_sButtonText[3]; // Left, Right, Wheel
public:
	MouseClickObserver();
	void update(MouseClickEvent state);
};
#endif
