/**
@file OBB.cpp
*/

#include "OBB.h"

OBB::OBB()
{
	m_dimensions.set(0.f,0.0f);
	m_position.set(0.0f, 0.0f);
	m_fOrientation = 0.0f;
	m_fCoeffElasticity = 1.0f;

	m_renderBox.setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	m_renderBox.setPosition(m_position.x(), m_position.y());
	m_renderBox.setRotation(m_fOrientation);
	m_renderBox.setOutlineColor(sf::Color::Transparent);
	m_renderBox.setFillColor(sf::Color::Transparent);
}	

OBB::OBB(Vector2D dimensions, Vector2D position, float orientation, float elasticity)
{
	m_dimensions = dimensions;
	m_position = position;
	m_fOrientation = orientation;
	m_fCoeffElasticity = elasticity;

	m_renderBox.setSize(sf::Vector2f(m_dimensions.x(), m_dimensions.y()));
	m_renderBox.setOrigin(m_dimensions.x()/2.0f, m_dimensions.y()/2.0f);
	m_renderBox.setPosition(m_position.x(), m_position.y());
	m_renderBox.setRotation(m_fOrientation);
	m_renderBox.setOutlineThickness(0.f);
	m_renderBox.setFillColor(sf::Color::Green);
}

void OBB::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_renderBox);
}

bool OBB::collided(Ball &ball, Vector2D &normal) //!< Has the ball collided with OBB
{
	// Rotate balls position by OBB orientation CCW

	// Move OBB to the origin
	Vector2D ballPos = ball.getPosition() - m_position; 

	// Rotate Ball CCW around origin (OBB centre)
	float theta = m_fOrientation * ((float)M_PI / 180.f);

	float newX = cos(theta) * ballPos.x() + sin(theta) * ballPos.y();
	float newY = (-sin(theta)) * ballPos.x() + cos(theta) * ballPos.y();

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
		return true;
	}
	return false;
}

float OBB::getCoeffElasticity()
{
	return m_fCoeffElasticity;
}
