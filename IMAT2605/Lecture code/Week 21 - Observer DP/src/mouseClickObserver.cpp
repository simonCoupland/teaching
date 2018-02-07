#include "MouseClickObserver.h"

MouseClickObserver::MouseClickObserver()
{
	a_sButtonText[0] = "Left";
	a_sButtonText[1] = "Right";
	a_sButtonText[2] = "Wheel";
}

void MouseClickObserver::update(MouseClickEvent state)
{
	cout << "Mouse button: " << a_sButtonText[state.getButton()];
	cout << " x: " << state.getX();
	cout << " y: " << state.getY() << endl;
}
