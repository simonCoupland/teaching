#include "MovingObject.h"
#include "paddle.h"

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


bool MovingObject::checkCollisions(Paddle& other) const
{
	return getGlobalBounds().intersects(other.getGlobalBounds());
}

Vector2f MovingObject::getVelocity()
{
	return m_velocity;
}

void MovingObject::setVelocity(Vector2f velocity)
{
	m_velocity = velocity;
}