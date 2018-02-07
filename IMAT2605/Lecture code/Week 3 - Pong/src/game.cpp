#include "game.h"

Game::Game()
{
	// Populate the game with different objects

	m_ballStartPosition = Vector2f(400.f, 300.f);

	m_ball = MovingObject(m_ballStartPosition, Vector2f(40.f, 40.f), Vector2f(125.f, 45.f), Color(60, 205, 60));
	
	m_paddle = Paddle(Vector2f(75.f, 300.f), Vector2f(40.f, 150.f), Color(255, 50, 50));
	m_aiPaddle = Paddle(Vector2f(725.f,300.f), Vector2f(40.f, 150.f), Color(255, 50, 50));
	m_aiPaddle.setVelocity(Vector2f(0.f, 140.f));

	m_aStaticObjects.at(0) = StaticObject(Vector2f(400.f, 20.f), Vector2f(800.f, 40.f), Color(60,60,205));
	m_aStaticObjects.at(1) = StaticObject(Vector2f(400.f, 580.f), Vector2f(800.f, 40.f), Color(60, 60, 205));
	m_aStaticObjects.at(2) = StaticObject(Vector2f(20.f, 300.f), Vector2f(40.f, 600.f), Color(60, 60, 205));
	m_aStaticObjects.at(3) = StaticObject(Vector2f(780.f, 300.f), Vector2f(40.f, 600.f), Color(60, 60, 205));
}

void Game::update(float time)
{
	// Update the ball
	m_ball.update(time);

	// Check for collisions
	if (m_ball.checkCollisions(m_paddle)) { m_ball.setVelocity(Vector2f(-m_ball.getVelocity().x, m_ball.getVelocity().y)); }
	if (m_aStaticObjects.at(0).checkCollisions(m_ball)) { m_ball.setVelocity(Vector2f(m_ball.getVelocity().x, -m_ball.getVelocity().y)); }
	if (m_aStaticObjects.at(1).checkCollisions(m_ball)) { m_ball.setVelocity(Vector2f(m_ball.getVelocity().x, -m_ball.getVelocity().y)); }
	if (m_aStaticObjects.at(3).checkCollisions(m_ball)) { m_ball.setVelocity(Vector2f(-m_ball.getVelocity().x, m_ball.getVelocity().y)); }

	m_aiPaddle.update(time);
	// Check for collisions
	if (m_ball.checkCollisions(m_aiPaddle)) { m_ball.setVelocity(Vector2f(-m_ball.getVelocity().x, m_ball.getVelocity().y)); }
	if (m_aStaticObjects.at(0).checkCollisions(m_aiPaddle)) { m_aiPaddle.setVelocity(Vector2f(m_aiPaddle.getVelocity().x, -m_aiPaddle.getVelocity().y)); }
	if (m_aStaticObjects.at(1).checkCollisions(m_aiPaddle)) { m_aiPaddle.setVelocity(Vector2f(m_aiPaddle.getVelocity().x, -m_aiPaddle.getVelocity().y)); }

	// Check for human paddle collision
	if (m_aStaticObjects.at(0).checkCollisions(m_paddle)) { m_paddle.setPosition(Vector2f(m_paddle.getPosition().x, 115.f)); }
	if (m_aStaticObjects.at(1).checkCollisions(m_paddle)) { m_paddle.setPosition(Vector2f(m_paddle.getPosition().x, 485.f)); }

}

void Game::draw(RenderTarget& target, RenderStates states) const
{
	// Draw all things that need to be drawn
	for (int i = 0; i < m_aStaticObjects.size(); i++) { target.draw(m_aStaticObjects.at(i)); }

	target.draw(m_paddle);
	target.draw(m_aiPaddle);
	target.draw(m_ball);
}

void Game::processEvent(Event& e)
{
	// Process and user events, keypresses, mouse clicks etc..
	m_paddle.processEvent(e);
}