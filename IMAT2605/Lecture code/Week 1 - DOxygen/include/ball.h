/**
@file ball.h
*/
#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

#include "textureLoader.h"
#include "vector2D.h"

class Ball : public sf::Drawable
{
private:
	sf::Sprite m_ballSprite; //!< Sprite to draw the ball
	float m_fRadius; //!< Radius of the ball in physical space
	float m_fInverseMass; //!< 1 / Mass of the ball
	Vector2D m_position; //!< Position of the ball
	Vector2D m_velocity; //!< Velocity of the ball
	Vector2D m_acceleration; //!< Acceleration of the ball
	float m_fCoeffElasticity; //!< Coefficient of elasticity of the ball
public:
	Ball(); //!< Constructor
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw function (from sf::Drawable)
	void update(float timestep); //!< Update the ball
	float getRadius(); //!< Return the ball radius
	Vector2D getPosition(); //!< Return the ball position
	float getCoeffElasticity(); //!< Returns the coefficient of elasticity
	void resolveStaticCollision(Vector2D collisionNormal, float coeffElasticity); //!< Change the balls velocity when hitting a static object
	void resolveDynamicCollision(Vector2D collisionNormal, float velocity, float coeffElasticity); //!< Change the balls velocity when hitting a static object
	void fire(); //!< shoot the ball
};

#endif