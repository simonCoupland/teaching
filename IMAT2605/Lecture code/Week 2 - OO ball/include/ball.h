#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

/*! A ball Class */
class Ball : public sf::Drawable
{
private:
	sf::Vector2f position; //!< Position of the ball in 2D space
	sf::Vector2f velocity; //!< Velocity of the ball
	sf::Vector2f acceleration; //!< Acceleration acting on the ball
	float fRadius; //!< Radius of the ball
	int iNumPoints; //!< Number of points used to draw the ball
public:
	Ball(float fxPos, float fyPos,float fxVel, float fyVel); //!< Constructor which takes position and velocity
	void updatePhysics(float fTimestep, float fLinePos); //!< Update the position of the ball
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Draw the ball
};

#endif