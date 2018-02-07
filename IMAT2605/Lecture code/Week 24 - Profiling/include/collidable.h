#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "movable.h"

class Collidable : public Movable
{
protected:
	float density; //!< How much mass per unit area
	virtual float area() = 0; //!< Size of the collidable object
	float inverseMass; //!< One over the amount of mass the object has
	float coeffElastisicty; //!< How much bounce an object has
	float coeffFriction; //!< How sticky an object is
	float torque;
	float inverseMomentOfInertia;
public:
	Collidable(); //!< Default constructor
	friend class Collisions;
};

#endif