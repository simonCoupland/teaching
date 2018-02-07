#include "fileLog.h"

FileLog::FileLog()
{
	a_sButtonText[0] = "Left";
	a_sButtonText[1] = "Right";
	a_sButtonText[2] = "Wheel";

	file.open("outputLog.txt");
}

FileLog::~FileLog()
{
	file.close();
}

void FileLog::update(MouseClickEvent state)
{
	file << "Mouse button: " << a_sButtonText[state.getButton()];
	file << " x: " << state.getX();
	file << " y: " << state.getY() << endl;
}