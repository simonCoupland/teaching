#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "box.h"
#include "ball.h"
#include "vector2D.h"

class Collisions
{
private:
public:
	void Resolve(Collidable &a, Collidable &b, Vector2D &normal);
	void ResolveWithRotation(Collidable &a, Collidable &b, Vector2D &normal, Vector2D &contactVectorA, Vector2D &contactVectorB);
	void PositionCorrection(Collidable &a, Collidable &b, float penetration, Vector2D &normal, float slop, float percent);
	bool AABBvsAABB(Box &a, Box &b, float &pentration, Vector2D &normal);
	bool AABBvsCIRCLE(Box &a, Ball &b, float &penetration, Vector2D &normal, Vector2D &contactVectorA, Vector2D &contactVectorB);
	bool CIRCLEvsCIRCLE(Ball &a, Ball &b, float &penetration, Vector2D &normal,Vector2D &contactVectorA, Vector2D &contactVectorB);
};

#endif
