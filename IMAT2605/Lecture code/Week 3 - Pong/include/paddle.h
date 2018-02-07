#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

#include "movingObject.h"

using namespace sf;

class Paddle : public MovingObject
{
public:
	Paddle(){};
	Paddle(Vector2f& position, Vector2f& dimensions, Color& color);
	void processEvent(Event& e);
};

#endif