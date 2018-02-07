/**
@file bumper.cpp
*/

#include "bumper.h"

Bumper::Bumper()
{
	m_fRadius = 0.f;
	m_fCoeffElasticity = 1.0f;
	m_position = Vector2D(0.f,0.f);

	m_renderCircle.setFillColor(sf::Color::Red);
	m_renderCircle.setOutlineThickness(0.0f);
	m_renderCircle.setRadius(m_fRadius);
	m_renderCircle.setPosition(m_position.x(), m_position.y());
	m_renderCircle.setOrigin(m_fRadius,m_fRadius);
}

Bumper::Bumper(Vector2D position)
{
	m_fRadius = 35.f;
	m_fCoeffElasticity = 1.0f;
	m_position = Vector2D(position);

	m_renderCircle.setFillColor(sf::Color::Red);
	m_renderCircle.setOutlineThickness(0.0f);
	m_renderCircle.setRadius(m_fRadius);
	m_renderCircle.setPosition(m_position.x(), m_position.y());
	m_renderCircle.setOrigin(m_fRadius,m_fRadius);
}

void Bumper::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_renderCircle);
}

float Bumper::getCoeffElasticity()
{
	return m_fCoeffElasticity;
}

bool Bumper::collided(Ball &ball, Vector2D &normal) //!< Has the ball collided with bumper
{
	Vector2D distance = ball.getPosition() - m_position;
	if(distance.magnitude() < (ball.getRadius() + m_fRadius))
	{
		normal = distance.unitVector();
		return true;
	}
	return false;
}
