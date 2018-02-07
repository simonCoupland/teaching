#include "box.h"

Box::Box(int wh, Vector2D &e, Vector2D &r, Vector2D &v, Vector2D &a, std::vector<sf::Texture>::iterator texIter, float cf)
{
	windowHeight = wh;
	extents = e;
	position = r;
	velocity = v;
	acceleration = a;
	angularVelocity = 0;
	orientationAngle = 0;
	torque = 0;
	inverseMomentOfInertia = 0;
	sprite.setTexture(*texIter);
	sprite.setScale(sf::Vector2f(2.0f*extents.getX()/texIter->getSize().x,2.0f*extents.getY()/texIter->getSize().y));
	sprite.setOrigin(extents.getX()/sprite.getScale().x,extents.getY()/sprite.getScale().y);
	inverseMass = 0.0f;
	coeffElastisicty = 1.0f;
	coeffFriction = cf;
}

Box::Box(int wh, Vector2D &e, Vector2D &r, Vector2D &v, Vector2D &a, float th, float w, std::vector<sf::Texture>::iterator texIter, float d, float ce, float cf)
{
	windowHeight = wh;
	extents = e;
	position = r;
	velocity = v;
	acceleration = a;
	angularVelocity = w;
	orientationAngle = th;
	sprite.setTexture(*texIter);
	sprite.setScale(sf::Vector2f(2.0f*extents.getX()/texIter->getSize().x,2.0f*extents.getY()/texIter->getSize().y));
	sprite.setOrigin(extents.getX()/sprite.getScale().x,extents.getY()/sprite.getScale().y);
	sprite.setPosition(r.getX(), r.getY());
	density = d;
	inverseMass = 1.0f / (area() * density);
	torque = 0.0f;
	inverseMomentOfInertia = 1.0f / (area() * density * (powf(2.0f * extents.getX(),2.0f) + powf(2.0f * extents.getY(),2.0f)) / 12.0f);
	coeffElastisicty = ce;
	coeffFriction = cf;
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

Vector2D Box::accelerationFunction(Vector2D &v)
{
	// air resitance and gravity
	float dragX = -(v.getX() * v.getX() * extents.getX() * 0.00001f);
	float dragY = -(v.getY() * v.getY() * extents.getY() * 0.00001f);;
	return Vector2D(dragX, -40.0f + dragY);
}

float Box::angularAccelerationFunction(float &w)
{
	return torque * inverseMomentOfInertia;
}

float Box::area()
{
	return ((2 * extents.getX()) * (2 * extents.getY()));
}

void Box::update()
{
	sprite.setPosition(position.getX(), windowHeight - position.getY());
	//sprite.setColor(sf::Color::Magenta);
}