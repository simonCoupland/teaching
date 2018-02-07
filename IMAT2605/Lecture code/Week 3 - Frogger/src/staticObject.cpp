#include "staticObject.h"

StaticObject::StaticObject(Vector2f& position, Vector2f& dimensions, Color& color)
{
	setPosition(position);
	setSize(dimensions);
	setOrigin(dimensions.x / 2.f, dimensions.y / 2.f);
	setFillColor(color);
}

bool StaticObject::checkCollisions(Character& other) const
{
	return getGlobalBounds().intersects( other.getGlobalBounds() );
}