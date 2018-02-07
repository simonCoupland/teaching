/**
@file OBB.h
*/

#ifndef OBB_H
#define OBB_H

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>

#include "vector2D.h"
#include "ball.h"

class OBB : public sf::Drawable
{
private:
	Vector2D m_dimensions; //!< Size of the OBB
	float m_fOrientation; //!< Angle in degrees
	Vector2D m_position; //!< Position of the OBB in 2D space
	float m_fCoeffElasticity; //!< Coefficient of elasticity of the OBB
	sf::RectangleShape m_renderBox; //!< thing drawn on the screen

public:
	OBB(); //!< Constructor
	OBB::OBB(Vector2D dimensions, Vector2D position, float orientation, float elasticity); //!< Constructor with params
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw function (from sf::Drawable)
	bool collided(Ball &ball, Vector2D &normal); //!< Has the ball collided with OBB
	float getCoeffElasticity(); //!< Returns the coefficient of elasticity
};

#endif