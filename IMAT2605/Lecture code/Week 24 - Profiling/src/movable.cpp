#include "movable.h"

Movable::Movable()
{
	acceleration = Vector2D(0);
	velocity = Vector2D(0);
	position = Vector2D(0);
}

void Movable::setPosition(Vector2D r)
{
	position = r;
}

void Movable::setVelocity(Vector2D v)
{
	velocity = v;
}

void Movable::setAcceleration(Vector2D a)
{
	acceleration = a;
}
	
void Movable::integrate(float time)
{
	// Improved Euler
	Vector2D EulerA;
	Vector2D EulerV;

	float EulerAA;
	float EulerW;

	acceleration = accelerationFunction(velocity);

	EulerV = velocity + (acceleration * time);
	EulerA = accelerationFunction(EulerV);

	velocity = velocity + ((acceleration + EulerA) * (time / 2.0f));
	position = position + ((velocity + EulerV) * (time / 2.0f));

	angularAcceleration = angularAccelerationFunction(angularVelocity);

	EulerW = angularVelocity + angularAcceleration * time;
	EulerAA = angularAccelerationFunction(EulerW);

	angularVelocity = angularVelocity + (angularAcceleration + EulerAA) * (time / 2.0f);
	orientationAngle = orientationAngle + (angularVelocity + EulerW) * (time / 2.0f);
}


