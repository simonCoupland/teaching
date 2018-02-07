#include "mouseClickSubscriber.h"


void MouseClickSubscriber::attach(MouseClickObserver* observer)
{
	observers.push_back(observer);
}

void MouseClickSubscriber::dettach(MouseClickObserver* observer)
{
	observers.erase(remove(observers.begin(), observers.end(), observer), observers.end()); 
}

void MouseClickSubscriber::notify(MouseClickEvent updatedState)
{
	for(auto observer : observers)
	{
		observer->update(updatedState);
	}
}