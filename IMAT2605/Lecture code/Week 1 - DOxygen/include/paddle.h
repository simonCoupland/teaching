/**
@file paddle.h
*/

#ifndef PADDLE_H
#define PADDLE_H

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <cmath>

#include "vector2D.h"
#include "ball.h"

class Paddle : public sf::Drawable
{
private:
	Vector2D m_origin; //!< POint which paddle rotates around
	Vector2D m_dimensions; //!< Size of the OBB
	float m_fOrientation; //!< Angle in degrees
	Vector2D m_position; //!< Position of the OBB in 2D space
	float m_fCoeffElasticity; //!< Coefficient of elasticity of the OBB
	sf::RectangleShape m_renderBox; //!< thing drawn on the screen
	float m_fAngularAcceleration; //!< Angular acceleration of the paddle
	float m_fGravitationAcceleration; //!< Acceleration due to gravity
	float m_fAngularVelocity; //!< Angular acceleration of the paddle
	float m_fMinOrientation; //!< Minimum Rotation position
	float m_fMaxOrientation; //!< Maximum Rotation position

public:
	Paddle(); //!< Constructor
	Paddle(Vector2D origin, Vector2D dimensions, Vector2D position, float coeffElasticity, float orientation, float minTheta, float maxTheta, float gravity); //!< Constructor with params
	void update(float timestep); //!< Update the paddle
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw function (from sf::Drawable)
	bool collided(Ball &ball, Vector2D &normal, float &velocity); //!< Has the ball collided with OBB
	float getCoeffElasticity(); //!< Returns the coefficient of elasticity
	void setAngularAcceleration(float angularAcceleration); //!< Set the angular acceleration
	
};

#endif