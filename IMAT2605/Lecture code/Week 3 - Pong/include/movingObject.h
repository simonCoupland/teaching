#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include <SFML/Graphics.hpp>

class Paddle;

using namespace sf;

class MovingObject : public RectangleShape
{
protected:
	Vector2f m_velocity;
public:
	MovingObject(){};
	MovingObject(Vector2f& position, Vector2f& dimensions, Vector2f& velocity, Color& color);
	void update(float time);
	bool checkCollisions(Paddle& other) const;
	Vector2f getVelocity();
	void setVelocity(Vector2f velocity);
};

#endif