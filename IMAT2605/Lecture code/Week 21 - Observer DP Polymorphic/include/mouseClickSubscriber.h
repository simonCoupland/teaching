#ifndef MOUSECLICKSUBSCRIBER_H
#define MOUSECLICKSUBSCRIBER_H

#include "MouseClickEvent.h"
#include "ConsoleLog.h"
#include "FileLog.h"
#include "widget.h"
#include <vector>
#include <algorithm>

using namespace std;

class MouseClickSubscriber
{
private :
	vector<MouseClickObserver *> observers;
public :
	void attach(MouseClickObserver * observer);
	void dettach(MouseClickObserver * observer);
	void notify(MouseClickEvent updatedState);
};
#endif