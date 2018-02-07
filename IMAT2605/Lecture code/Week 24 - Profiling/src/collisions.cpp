#include "collisions.h"

void Collisions::Resolve(Collidable &a, Collidable &b, Vector2D &normal)
{
	// Calculate relative velocity
	Vector2D rv = b.velocity - a.velocity;
 
	// Calculate relative velocity along the normal
	float velAlongNormal = rv.dotProduct(normal);
 
	// Do not resolve if velocities are separating
	if(velAlongNormal > 0)
	return;
 
	// Calculate elasticity
	float e = std::min(a.coeffElastisicty, b.coeffElastisicty);
 

	// Calculate impulse scalar
	float j =  -(1.0f + e) * velAlongNormal / (a.inverseMass + b.inverseMass);

	// Apply impulse
	Vector2D impulse = normal * j;
	a.velocity = a.velocity - (impulse * a.inverseMass);
	b.velocity = b.velocity + (impulse * b.inverseMass);

	// Calculate new relative velocity
	rv = b.velocity - a.velocity;
 
	// Velocity along the normal
	velAlongNormal = rv.dotProduct(normal);

	// Identify velocity along the tangent
	Vector2D tangent = rv - (normal * velAlongNormal);
	
	// Normalise
	if(tangent.getX() * tangent.getX() + tangent.getY() * tangent.getY() > 0)
	{
		tangent = tangent.getUnitVector();
	}
	else
	{
		// no velocity along the tangent
		return;
	}
 
	// Find velocity along tangent as a scalar

	float jt = -rv.dotProduct(tangent);
	jt = jt / (a.inverseMass + b.inverseMass);

	float mu = sqrtf(powf(a.coeffFriction,2.0f)+powf(b.coeffFriction,2.0f));
	
	Vector2D frictionImpulse;
	// Clamp magnitude of friction and create impulse vector
	if(fabs(jt) < j * mu) 
	{
		frictionImpulse = tangent * jt;
	}
	else
	{
	  frictionImpulse = tangent * (mu * -j);
	}
	// Apply friction impulse
	a.velocity = a.velocity - (frictionImpulse * a.inverseMass);
	b.velocity = b.velocity + (frictionImpulse * b.inverseMass);
}

void Collisions::ResolveWithRotation(Collidable &a, Collidable &b, Vector2D &normal, Vector2D &contactVectorA, Vector2D &contactVectorB)
{
		// Calculate relative velocity
	Vector2D rv = b.velocity + contactVectorB.crossProduct(b.angularVelocity) - a.velocity - contactVectorA.crossProduct(a.angularVelocity);
 
	// Calculate relative velocity along the normal
	float velAlongNormal = rv.dotProduct(normal);
 
	// Do not resolve if velocities are separating
	if(velAlongNormal > 0)
	return;
 
	// Calculate elasticity
	float e = std::min(a.coeffElastisicty, b.coeffElastisicty);

	// Calculate denominator
	float dom = a.inverseMass + b.inverseMass + powf(contactVectorA.crossProduct(normal),2.0f) * a.inverseMomentOfInertia + powf(contactVectorB.crossProduct(normal),2.0f) * b.inverseMomentOfInertia;
	// Calculate impulse scalar
	float j =  -(1.0f + e) * velAlongNormal / dom;

	// Apply impulse
	Vector2D impulse = normal * j;
	a.velocity = a.velocity - (impulse * a.inverseMass);
	b.velocity = b.velocity + (impulse * b.inverseMass);

	a.angularVelocity = a.angularVelocity + contactVectorA.crossProduct(impulse) * a.inverseMomentOfInertia;
	b.angularVelocity = b.angularVelocity + contactVectorB.crossProduct(impulse) * b.inverseMomentOfInertia;

	// Calculate new relative velocity
	rv = b.velocity + contactVectorB.crossProduct(b.angularVelocity) - a.velocity - contactVectorA.crossProduct(a.angularVelocity);
 
	// Velocity along the normal
	velAlongNormal = rv.dotProduct(normal);

	// Identify velocity along the tangent
	Vector2D tangent = rv - (normal * velAlongNormal);
	
	// Normalise
	if(tangent.getX() * tangent.getX() + tangent.getY() * tangent.getY() > 0)
	{
		tangent = tangent.getUnitVector();
	}
	else
	{
		// no velocity along the tangent
		return;
	}
 
	// Find velocity along tangent as a scalar

	float jt = -rv.dotProduct(tangent);
	jt = jt / (a.inverseMass + b.inverseMass);

	float mu = sqrtf(powf(a.coeffFriction,2.0f)+powf(b.coeffFriction,2.0f));
	
	Vector2D frictionImpulse;
	// Clamp magnitude of friction and create impulse vector
	if(fabs(jt) < j * mu) 
	{
		frictionImpulse = tangent * jt;
	}
	else
	{
	  frictionImpulse = tangent * (mu * -j);
	}
	// Apply friction impulse
	a.velocity = a.velocity - (frictionImpulse * a.inverseMass);
	b.velocity = b.velocity + (frictionImpulse * b.inverseMass);

	a.angularVelocity = a.angularVelocity + contactVectorA.crossProduct(frictionImpulse) * a.inverseMomentOfInertia;
	b.angularVelocity = b.angularVelocity + contactVectorB.crossProduct(frictionImpulse) * b.inverseMomentOfInertia;
}

void Collisions::PositionCorrection(Collidable &a, Collidable &b, float penetration, Vector2D &normal, float slop, float percent)
{
	Vector2D correction = normal * ((std::max(penetration - slop, 0.0f) / (a.inverseMass + b.inverseMass)) * percent);
	a.position = (a.position - (correction * a.inverseMass));
	b.position = (b.position + (correction * b.inverseMass));
}

bool Collisions::AABBvsAABB(Box &a, Box &b, float &penetration, Vector2D &normal)
{
	Vector2D diff = b.position - a.position;

	float overlapX = a.extents.getX() + b.extents.getX() - fabs(diff.getX());
	
	if(overlapX > 0) // AABBs overlap in x axis
	{
		float overlapY = a.extents.getY() + b.extents.getY() - fabs(diff.getY());
		if(overlapY > 0) // AABBs overlap in y axis
		{
			// Identify axis of least penetration
			if(overlapX < overlapY)
			{
				penetration = overlapX;
				if(diff.getX() < 0) normal = Vector2D(-1,0);
				else normal = Vector2D(1,0);
			}
			else
			{
				penetration = overlapY;
				if(diff.getY() < 0) normal = Vector2D(0,-1);
				else normal = Vector2D(0,1);
			}
			return true;
		}
	}
	return false;
}

bool Collisions::AABBvsCIRCLE(Box &a, Ball &b, float &penetration, Vector2D &normal, Vector2D &contactVectorA, Vector2D &contactVectorB)
{
	// Move ball into circles space
	Vector2D diff = b.position - a.position;

	float r00, r01, r10, r11;
	r00 = cos(a.orientationAngle);
	r01 = -sin(a.orientationAngle);
	r10 = -r01;
	r11 = r00;
	float newI = diff.getX() * r00 + diff.getY() * r01;
	float newJ = diff.getX() * r10 + diff.getY() * r11; 

	diff.set(newI,newJ);
	float clampX, clampY;

	if(diff.getX() < 0) clampX = std::max(diff.getX(),-a.extents.getX());
	else clampX = std::min(diff.getX(),a.extents.getX());

	if(diff.getY() < 0) clampY = std::max(diff.getY(),-a.extents.getY());
	else clampY = std::min(diff.getY(),a.extents.getY());

	Vector2D clamp(clampX, clampY);
	Vector2D dist = diff - clamp;

	penetration = -(dist.magnitude() - b.radius);

	normal = (diff-clamp).getUnitVector();

	contactVectorA = clamp;
	contactVectorB = b.position - (a.position + clamp);

	return penetration > 0;
}

bool Collisions::CIRCLEvsCIRCLE(Ball &a, Ball &b, float &penetration, Vector2D &normal,Vector2D &contactVectorA, Vector2D &contactVectorB)
{
	Vector2D diff = b.position - a.position;
	penetration = -(diff.magnitude() - sqrt(powf(a.radius+ b.radius,2.0f)));
	normal = diff.getUnitVector();

	if (penetration > 0){
	float scalar = a.radius / (a.radius + b.radius);
	Vector2D contactPoint = a.position + (diff * scalar);
	contactVectorA = (diff * -scalar);
	contactVectorB = (diff * (1.0f-scalar));
	}
	return penetration > 0;
}