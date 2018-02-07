#include  "consoleLog.h"

ConsoleLog::ConsoleLog()
{
	a_sButtonText[0] = "Left";
	a_sButtonText[1] = "Right";
	a_sButtonText[2] = "Wheel";
}

void ConsoleLog::update(MouseClickEvent state)
{
	cout << "Mouse button: " << a_sButtonText[state.getButton()];
	cout << " x: " << state.getX();
	cout << " y: " << state.getY() << endl;
}