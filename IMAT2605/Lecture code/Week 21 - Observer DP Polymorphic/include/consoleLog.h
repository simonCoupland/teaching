#ifndef CONSOLELOG_H
#define CONSOLELOG_H

#include "MouseClickObserver.h"

#include <string>
#include <iostream>

class ConsoleLog : public MouseClickObserver
{
private:
	string a_sButtonText[3];
public:
ConsoleLog();
void update(MouseClickEvent state);

};

#endif
