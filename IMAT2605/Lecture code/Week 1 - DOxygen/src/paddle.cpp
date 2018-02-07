/**
@file paddle.cpp
*/

#include "paddle.h"

Paddle::Paddle()
{
}

Paddle::Paddle(Vector2D origin, Vector2D dimensions, Vector2D position, float coeffElasticity, float orientation, float minTheta, float maxTheta, float gravity)
{
	m_origin = origin;
	m_dimensions = dimensions;
	m_fOrientation = orientation;
	m_position = position;
	m_fCoeffElasticity = coeffElasticity;
	m_fMinOrientation = minTheta;
	m_fMaxOrientation = maxTheta;
	m_fAngularAcceleration = 0.f;
	m_fGravitationAcceleration = gravity;
	m_fAngularVelocity = 0.f;

	m_renderBox.setOrigin(m_origin.x(), m_origin.y());
	m_renderBox.setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	m_renderBox.setPosition(m_position.x(), m_position.y());
	m_renderBox.setRotation(m_fOrientation);
	m_renderBox.setOutlineThickness(0.f);
	m_renderBox.setFillColor(sf::Color::Red);
}

void Paddle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_renderBox);
}

bool Paddle::collided(Ball &ball, Vector2D &normal, float &velocity) //!< Has the ball collided with OBB
{
	// Rotate balls position by OBB orientation CCW

	// Move OBB to the origin
	Vector2D centre;
	centre = (m_dimensions * 0.5f) - m_origin;

	// Rotate to centre by orientation
	float theta = m_fOrientation * ((float)M_PI / 180.f);

	float newX = cos(theta) * centre.x() - sin(theta) * centre.y();
	float newY = sin(theta) * centre.x() + cos(theta) * centre.y();

	Vector2D ballPos =  ball.getPosition() - (Vector2D(newX, newY) + m_position); 

	// Rotate Ball CCW around origin (OBB centre)

	newX = cos(theta) * ballPos.x() + sin(theta) * ballPos.y();
	newY = (-sin(theta)) * ballPos.x() + cos(theta) * ballPos.y();

	ballPos.set(newX, newY);

	// Check for collision

	// Find distance
	Vector2D distance(-ballPos.x(), -ballPos.y());

	// Clamp distance
	Vector2D clamp = distance;
	if(distance.x() < 0 && distance.x() < -m_dimensions.x()/2.0f)  clamp.set(-m_dimensions.x()/2.0f, clamp.y());
	if(distance.x() > 0 && distance.x() > m_dimensions.x()/2.0f)  clamp.set(m_dimensions.x()/2.0f, clamp.y());
	if(distance.y() < 0 && distance.y() < -m_dimensions.y()/2.0f)  clamp.set(clamp.x(), -m_dimensions.y()/2.0f);
	if(distance.y() > 0 && distance.y() > m_dimensions.y()/2.0f)  clamp.set(clamp.x(), m_dimensions.y()/2.0f);

	// Find the difference
	Vector2D difference = distance - clamp;

	
	if(difference.magnitude() < ball.getRadius())
	{
		// Rotate back
		newX = cos(theta) * difference.x() - sin(theta) * difference.y();
		newY = sin(theta) * difference.x() + cos(theta) * difference.y();

		// Set collision normal
		normal.set(-newX, -newY);
		normal = normal.unitVector();

		// Calculate the velocity of the paddle at the point of impact
		velocity = 400.f;
		return true;
	}
	return false;
}

float Paddle::getCoeffElasticity()
{
	return m_fCoeffElasticity;
}

void Paddle::update(float timestep) //!< Update the paddle
{
	// Simple Euler
	m_fAngularVelocity = m_fAngularVelocity + timestep * (m_fAngularAcceleration + m_fGravitationAcceleration);
	float newOrientation = m_fOrientation + timestep * (m_fAngularVelocity);

	if(newOrientation > m_fMaxOrientation)
	{
		m_fOrientation = m_fMaxOrientation;
		m_fAngularVelocity = 0;
		m_fAngularAcceleration = 0;
	}
	else if (newOrientation < m_fMinOrientation)
	{
		m_fOrientation = m_fMinOrientation;
		m_fAngularVelocity = 0;
		m_fAngularAcceleration = 0;
	}
	else 
	{
		m_fOrientation = newOrientation;
	}
	m_renderBox.setRotation(m_fOrientation);
}

void Paddle::setAngularAcceleration(float angularAcceleration)
{
	m_fAngularAcceleration = angularAcceleration;
}