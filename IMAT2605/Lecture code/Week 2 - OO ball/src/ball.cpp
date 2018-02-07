#include "ball.h"

Ball::Ball (float fxPos, float fyPos,float fxVel, float fyVel)
{
	position.x = fxPos;
	position.y = fyPos;

	velocity.x = fxVel;
	velocity.y = fyVel;

	acceleration.x = 0.0f;
	acceleration.y = 100.0f;

	fRadius = 35.0f;
	iNumPoints = 60;
}

void Ball::updatePhysics(float fTimestep, float fLinePos)
{
	// Update velocity and position use Euler
	velocity = velocity + acceleration * fTimestep;
	position = position + velocity * fTimestep;

	// Check for a collision
	if(position.y + fRadius > fLinePos)
	{
		// Ball has gone below the line
		position.y = fLinePos-fRadius;
		velocity.y = -velocity.y * 0.8;
	}
	
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray circle(sf::LinesStrip, iNumPoints+1);
	float ft = 0.0f;
	float fdetlaT = 6.28319 / (float)(iNumPoints-1);
	float fx,fy;
	
	for(int i=0;i < iNumPoints+1;i++)
	{
		fx = cos(ft) * fRadius;
		fy = sin(ft) * fRadius;
		ft = ft + fdetlaT;
		circle[i] = sf::Vertex(sf::Vector2f(position.x + fx,position.y + fy),sf::Color::Blue);
	}

	target.draw(circle);
}