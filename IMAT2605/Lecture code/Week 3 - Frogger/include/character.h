#ifndef CHARACTER_OBJECT_H
#define CHARACTER_OBJECT_H

#include "movingObject.h"

class Character : public MovingObject
{
public:
	Character(){};
	Character(Vector2f& position, Vector2f& dimensions, Color& color);
	void processEvent(Event& e);
	void setVelocity(Vector2f &velocity);
	
};
#endif