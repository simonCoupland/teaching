#include "game.h"

Game::Game()
{
	// Populate the game with different objects

	characterStartPosition = Vector2f(400.f, 575.f);
	m_character = Character(characterStartPosition, Vector2f(50.f, 50.f), Color(60, 205, 60));

	m_aStaticObjects.at(0) = StaticObject(Vector2f(400.f, 575.f), Vector2f(800.f, 50.f), Color(60,60,205));
	m_aStaticObjects.at(1) = StaticObject(Vector2f(400.f, 300.f), Vector2f(800.f, 50.f), Color(60, 60, 205));
	m_aStaticObjects.at(2) = StaticObject(Vector2f(400.f, 25.f), Vector2f(800.f, 50.f), Color(60, 60, 205));
	m_aStaticObjects.at(3) = StaticObject(Vector2f(400.f, 437.5f), Vector2f(800.f, 225.f), Color(80, 80, 80));
	m_aStaticObjects.at(4) = StaticObject(Vector2f(400.f, 162.5f), Vector2f(800.f, 225.f), Color(60, 180, 255));

	m_aCarryingObjects.at(0) = MovingObject(Vector2f(400.f, 112.5f), Vector2f(100.f, 50.f), Vector2f(100.f,0.f), Color(205, 60, 205));
	m_aCarryingObjects.at(1) = MovingObject(Vector2f(550.f, 112.5f), Vector2f(100.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 205));
	m_aCarryingObjects.at(2) = MovingObject(Vector2f(700.f, 112.5f), Vector2f(100.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 205));

	m_aCarryingObjects.at(3) = MovingObject(Vector2f(600.f, 175.f), Vector2f(200.f, 50.f), Vector2f(-100.f, 0.f), Color(205, 60, 205));
	m_aCarryingObjects.at(4) = MovingObject(Vector2f(900.f, 175.f), Vector2f(200.f, 50.f), Vector2f(-100.f, 0.f), Color(205, 60, 205));

	m_aCarryingObjects.at(5) = MovingObject(Vector2f(-300.f, 237.5f), Vector2f(100.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 205));
	m_aCarryingObjects.at(6) = MovingObject(Vector2f(-150.f, 237.5f), Vector2f(100.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 205));
	m_aCarryingObjects.at(7) = MovingObject(Vector2f(0.f, 237.5f), Vector2f(100.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 205));

	m_aCrashingObjects.at(0) = MovingObject(Vector2f(200.f, 362.5f), Vector2f(50.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 60));
	m_aCrashingObjects.at(1) = MovingObject(Vector2f(275.f, 362.5f), Vector2f(50.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 60));
	m_aCrashingObjects.at(2) = MovingObject(Vector2f(350.f, 362.5f), Vector2f(50.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 60));

	m_aCrashingObjects.at(3) = MovingObject(Vector2f(0.f, 425.f), Vector2f(50.f, 50.f), Vector2f(-100.f, 0.f), Color(205, 60, 60));
	m_aCrashingObjects.at(3) = MovingObject(Vector2f(220.f, 425.f), Vector2f(100.f, 50.f), Vector2f(-100.f, 0.f), Color(205, 60, 60));

	m_aCrashingObjects.at(5) = MovingObject(Vector2f(600.f, 487.5f), Vector2f(50.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 60));
	m_aCrashingObjects.at(6) = MovingObject(Vector2f(675.f, 487.5f), Vector2f(50.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 60));
	m_aCrashingObjects.at(7) = MovingObject(Vector2f(750.f, 487.5f), Vector2f(50.f, 50.f), Vector2f(100.f, 0.f), Color(205, 60, 60));

}

void Game::update(float time)
{
	// Update all the objects in the game that need updating
	for (int i = 0; i < m_aCrashingObjects.size(); i++) 
	{ 
		m_aCrashingObjects.at(i).update(time); 
		if (m_aCrashingObjects.at(i).getPosition().x < -300) m_aCrashingObjects.at(i).setPosition(m_aCrashingObjects.at(i).getPosition() + Vector2f(1300.f, 0.f));
		if (m_aCrashingObjects.at(i).getPosition().x > 1100) m_aCrashingObjects.at(i).setPosition(m_aCrashingObjects.at(i).getPosition() - Vector2f(1300.f, 0.f));
	}

	for (int i = 0; i < m_aCarryingObjects.size(); i++) 
	{ 
		m_aCarryingObjects.at(i).update(time); 
		if (m_aCarryingObjects.at(i).getPosition().x < -300) m_aCarryingObjects.at(i).setPosition(m_aCarryingObjects.at(i).getPosition() + Vector2f(1300.f, 0.f));
		if (m_aCarryingObjects.at(i).getPosition().x > 1100) m_aCarryingObjects.at(i).setPosition(m_aCarryingObjects.at(i).getPosition() - Vector2f(1300.f, 0.f));
	}

	// Check for any colisions and take appropriate action

	for (int i = 0; i < m_aCrashingObjects.size(); i++) 
	{
		if (m_aCrashingObjects.at(i).checkCollisions(m_character))
		{
			m_character.setPosition(characterStartPosition);
		}
	}

	// Set if the character is being carried

	// Initialise a boolean to check if it's being carried
	bool carried = false;
	// Set the characters velocity to zero
	m_character.setVelocity(Vector2f(0.f, 0.f));
	
	for (int i = 0; i < m_aCarryingObjects.size(); i++)
	{
		if (m_aCarryingObjects.at(i).checkCollisions(m_character))
		{
			m_character.setVelocity(m_aCarryingObjects.at(i).getVelocity());
			carried = true;
		}
	}

	// Check for water collision
	if (!carried && m_aStaticObjects.at(4).checkCollisions(m_character))
	{
		m_character.setPosition(characterStartPosition);
	}

	m_character.update(time);
}

void Game::draw(RenderTarget& target, RenderStates states) const
{
	// Draw all things that need to be drawn
	for (int i = 0; i < m_aStaticObjects.size(); i++) { target.draw(m_aStaticObjects.at(i)); }

	for (int i = 0; i < m_aCrashingObjects.size(); i++) { target.draw(m_aCrashingObjects.at(i)); }

	for (int i = 0; i < m_aCarryingObjects.size(); i++) {target.draw(m_aCarryingObjects.at(i)); }

	target.draw(m_character);
}

void Game::processEvent(Event& e)
{
	// Process and user events, keypresses, mouse clicks etc..
	m_character.processEvent(e);
}