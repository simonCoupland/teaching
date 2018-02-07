#ifndef MOVABLE_H
#define MOVABLE_H

#include "vector2D.h"
#include <SFML/Graphics.hpp>


class Movable {
protected:
	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;
	virtual Vector2D accelerationFunction(Vector2D &v) = 0;
	float orientationAngle;	
	float angularVelocity;
	float angularAcceleration;
	virtual float angularAccelerationFunction(float &w) = 0;
public:

	Movable();
	void setPosition(Vector2D r);
	void setVelocity(Vector2D v);
	void setAcceleration(Vector2D a);
	void integrate(float time);
	friend class Collisions;
};					
#endif