#include "ball.h"

Ball::Ball(int wh, float rad, Vector2D &r, Vector2D &v, Vector2D &a, float th, float w, std::vector<sf::Texture>::iterator texIter, float cf)
{
	windowHeight = wh;
	radius = rad;
	position = r;
	velocity = v;
	acceleration = a;
	angularVelocity = w;
	orientationAngle = th;
	sprite.setTexture(*texIter);
	inverseMass = 0.0f;
	torque = 0;
	inverseMomentOfInertia = 0;
	coeffElastisicty = 0.5;
	coeffFriction = cf;
}

Ball::Ball(int wh, float rad, Vector2D &r, Vector2D &v, Vector2D &a, float th, float w, std::vector<sf::Texture>::iterator texIter, float d, float ce, float cf)
{
	windowHeight = wh;
	radius = rad;
	position = r;
	velocity = v;
	acceleration = a;
	angularVelocity = w;
	orientationAngle = th;
	sprite.setTexture(*texIter);
	sprite.setScale(sf::Vector2f(2.0f*radius/texIter->getSize().x,2.0f*radius/texIter->getSize().y));
	sprite.setOrigin(radius/sprite.getScale().x,radius/sprite.getScale().y);
	density = d;
	inverseMass = 1.0f / (area() * density);
	torque = 0;
	inverseMomentOfInertia = 1.0f / ((area() * density) * powf(radius,2.0f) / 4.0f);
	coeffElastisicty = ce;
	coeffFriction = cf;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void Ball::update()
{
	sprite.setRotation(orientationAngle * 6.2831853f);
	sprite.setPosition(position.getX(), windowHeight - position.getY());
}

Vector2D Ball::accelerationFunction(Vector2D &v)
{
	// air resitance and gravity
	float dragX = -(v.getX() * v.getX() * radius * 0.00001f);
	float dragY = -(v.getY() * v.getY() * radius * 0.00001f);;
	return Vector2D(dragX, -40.0f + dragY);
}

float Ball::angularAccelerationFunction(float &w)
{
	return torque * inverseMomentOfInertia;
}

float Ball::area() //  Pi * r^2
{
	return 3.14159265f * radius * radius;
}

float Ball::centreX()
{
	return position.getX();
}