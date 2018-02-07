#include "MovingObject.h"
#include "Character.h"

MovingObject::MovingObject(Vector2f& position, Vector2f& dimensions, Vector2f& velocity, Color& color)
{
	setPosition(position);
	setSize(dimensions);
	setOrigin(dimensions.x / 2.f, dimensions.y / 2.f);
	setFillColor(color);
	m_velocity = velocity;
}

void MovingObject::update(float time)
{
	Vector2f newPosition = getPosition() + (m_velocity * time);
	setPosition(newPosition);
}


bool MovingObject::checkCollisions(Character& other) const
{
	return getGlobalBounds().intersects(other.getGlobalBounds());
}

Vector2f MovingObject::getVelocity()
{
	return m_velocity;
}