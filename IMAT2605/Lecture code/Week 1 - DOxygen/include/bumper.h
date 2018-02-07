/**
@file bumper.h
*/

#ifndef BUMPER_H
#define BUMPER_H

#include <SFML/Graphics.hpp>

#include "vector2D.h"
#include "ball.h"

class Bumper : public sf::Drawable
{
private:
	float m_fRadius; //!< Radius of the ball in physical space
	Vector2D m_position; //!< Position of the ball
	float m_fCoeffElasticity; //!< Coefficient of elasticity of the ball
	sf::CircleShape m_renderCircle; //!< Circle to be drawn
public:
	Bumper(); //!< Constructor
	Bumper::Bumper(Vector2D position);  //!< Constructor with params
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw function (from sf::Drawable)
	bool collided(Ball &ball, Vector2D &normal); //!< Has the ball collided with OBB
	float getCoeffElasticity(); //!< Returns the coefficient of elasticity
};

#endif