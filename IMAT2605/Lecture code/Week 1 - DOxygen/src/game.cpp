/**
@file game.cpp
*/

#include "game.h"

Game::Game()
{
	// Load textures
	pm_textureLoader = pm_textureLoader->instance();

	// Set the texture for the background texture
	m_backgroundSprite.setTexture(* pm_textureLoader->getTexture(0));

	// Populate OBBs
	m_obbs.resize(18);
	m_obbs[0] = OBB(Vector2D(50.f,5.f), Vector2D(410.f,550.f),0.f,    0.0f);
	m_obbs[1] = OBB(Vector2D(5.f,400.f), Vector2D(433.f,350.f),0.f,   0.05f);
	m_obbs[2] = OBB(Vector2D(5.f,400.f), Vector2D(387.f,350.f),0.f,   0.05f);
	m_obbs[3] = OBB(Vector2D(50.f,50.f), Vector2D(453.f,123.f),-5.f,  0.05f);
	m_obbs[4] = OBB(Vector2D(50.f,50.f), Vector2D(440.f,69.f),-20.f,  0.05f);
	m_obbs[5] = OBB(Vector2D(50.f,50.f), Vector2D(405.f,21.f),-50.f,  0.05f);
	m_obbs[6] = OBB(Vector2D(50.f,50.f), Vector2D(360.f,0.f),10.f,    0.05f);
	m_obbs[7] = OBB(Vector2D(200.f,50.f),Vector2D(231.f,-5.f),0.f,   0.05f);
	m_obbs[8] = OBB(Vector2D(30.f,30.f), Vector2D(120.f,8.f),-10.f,   0.05f);
	m_obbs[9] = OBB(Vector2D(30.f,30.f), Vector2D(90.f,17.f),-20.f,   0.05f);
	m_obbs[10] = OBB(Vector2D(30.f,30.f), Vector2D(61.f,32.f),-35.f,  0.05f);
	m_obbs[11] = OBB(Vector2D(30.f,30.f), Vector2D(36.5f,56.5f),-55.f,0.05f);
	m_obbs[12] = OBB(Vector2D(30.f,30.f), Vector2D(21.f,85.f),-70.f,  0.05f);
	m_obbs[13] = OBB(Vector2D(30.f,30.f), Vector2D(12.5f,116.f),-80.f,0.05f);
	m_obbs[14] = OBB(Vector2D(30.f,475.f), Vector2D(10.f,350.f),0.f,  0.05f);
	m_obbs[15] = OBB(Vector2D(77.f,10.f), Vector2D(60.f,525.f),15.f,0.05f);
	m_obbs[16] = OBB(Vector2D(80.f,10.f), Vector2D(348.f,525.f),-15.f,0.05f);
	m_obbs[17] = OBB(Vector2D(50.f,50.f), Vector2D(203.5f,600.f),45.f,0.05f);

	// Populate bumpers
	m_bumpers.resize(3);
	m_bumpers[0] = Bumper(Vector2D(140.f,220.f));
	m_bumpers[1] = Bumper(Vector2D(290.f,220.f));
	m_bumpers[2] = Bumper(Vector2D(215.f,120.f));

	// Set paddles
	m_leftPaddle = Paddle(Vector2D(0.f, 0.f),Vector2D(70.f,10.f),Vector2D(97.f, 530.f),0.7f,20.f,-50.f, 20.f, 4000.f);
	m_rightPaddle = Paddle(Vector2D(70.f, 0.f),Vector2D(70.f,10.f),Vector2D(307.f, 530.f),0.7f,-20.f,-20.f, 50.f, -4000.f);

	m_leftPaddleActive = false;
	m_rightPaddleActive = false;
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_backgroundSprite);
	
	for(std::vector<OBB>::const_iterator it = m_obbs.cbegin(); it != m_obbs.cend(); ++it)
	{
		target.draw(*it);
	}

	for(std::vector<Bumper>::const_iterator it = m_bumpers.cbegin(); it != m_bumpers.cend(); ++it)
	{
		target.draw(*it);
	}

	target.draw(m_leftPaddle);
	target.draw(m_rightPaddle);
	target.draw(m_ball);
}

void Game::update(float timestep)
{
	m_ball.update(timestep);

	if(m_leftPaddleActive) m_leftPaddle.setAngularAcceleration(-14000.f);
	m_leftPaddle.update(timestep);

	if(m_rightPaddleActive) m_rightPaddle.setAngularAcceleration(14000.f);
	m_rightPaddle.update(timestep);

	// Check for collisions
	Vector2D collisionNormal;
	for(std::vector<OBB>::iterator it = m_obbs.begin(); it != m_obbs.end(); ++it)
	{
		if(it->collided(m_ball, collisionNormal))
		{
			m_ball.resolveStaticCollision(collisionNormal, std::min(m_ball.getCoeffElasticity(), it->getCoeffElasticity()));
		}
	}

	for(std::vector<Bumper>::iterator it = m_bumpers.begin(); it != m_bumpers.end(); ++it)
	{
		if(it->collided(m_ball, collisionNormal))
		{
			m_ball.resolveStaticCollision(collisionNormal, it->getCoeffElasticity());
		}
	}

	float velocity;
	if(m_leftPaddle.collided(m_ball, collisionNormal, velocity))
	{
		if(m_leftPaddleActive)
		{
			m_ball.resolveDynamicCollision(collisionNormal, velocity, std::min(m_ball.getCoeffElasticity(), m_leftPaddle.getCoeffElasticity()));
		}
		else
		{
			m_ball.resolveDynamicCollision(collisionNormal, 5.f, std::min(m_ball.getCoeffElasticity(), m_leftPaddle.getCoeffElasticity()));
		}
	}

	if(m_rightPaddle.collided(m_ball, collisionNormal, velocity))
	{
		if(m_rightPaddleActive)
		{
			m_ball.resolveDynamicCollision(collisionNormal, velocity, std::min(m_ball.getCoeffElasticity(), m_rightPaddle.getCoeffElasticity()));
		}
		else
		{
			m_ball.resolveDynamicCollision(collisionNormal, 5.f, std::min(m_ball.getCoeffElasticity(), m_rightPaddle.getCoeffElasticity()));
		}
	}

	// Check for spring collision
	m_springActive = m_obbs[0].collided(m_ball,Vector2D());
}

void Game::processKeyPress(sf::Keyboard::Key code)
{
	if(code == sf::Keyboard::Key::A) m_leftPaddleActive = true;
	if(code == sf::Keyboard::Key::L) m_rightPaddleActive = true;
	if(code == sf::Keyboard::Key::Space && m_springActive) m_ball.fire();
}

void Game::processKeyRelease(sf::Keyboard::Key code)
{
	if(code == sf::Keyboard::Key::A) m_leftPaddleActive = false;
	if(code == sf::Keyboard::Key::L) m_rightPaddleActive = false;
}
