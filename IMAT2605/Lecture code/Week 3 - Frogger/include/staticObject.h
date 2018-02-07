#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include <SFML/Graphics.hpp>

#include "character.h"

using namespace sf;

class StaticObject : public RectangleShape 
{
public:
	StaticObject(){};
	StaticObject(Vector2f& position, Vector2f& dimensions, Color& color);
	bool checkCollisions(Character& other) const;
};
#endif