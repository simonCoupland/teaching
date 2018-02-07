#ifndef MOUSECLICKOBSERVER_H
#define MOUSECLICKOBSERVER_H

#include "MouseClickEvent.h"

using namespace std;

class MouseClickObserver
{
private:
public:
	virtual void update(MouseClickEvent state) = 0;
};
#endif
