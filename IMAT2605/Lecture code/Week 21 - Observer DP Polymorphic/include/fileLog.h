#ifndef FILELOG_H
#define FILELOG_H

#include "MouseClickObserver.h"

#include <string>
#include <iostream>
#include <fstream>

class FileLog : public MouseClickObserver
{
private:
	ofstream file;
	string a_sButtonText[3];
public:
FileLog();
~FileLog();
void update(MouseClickEvent state);

};

#endif
