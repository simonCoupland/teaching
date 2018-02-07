/*!
\file game.cpp
*/
#include "game.h"

Game::Game()
{
	m_view.setCenter(0.f, 0.f);
	m_view.setSize(m_worldSize);

	m_pWorld = new b2World(mk_gravity);

	// This could all be read in from a file, for now hard coded magic numbers
	// Shouldn't really use push back, better to pre allocate and assign
	// Infact to do this properly I should use the factory pattern witha  level file parser
	m_staticBlocks.push_back(new StaticBlock(m_pWorld, m_view, sf::Vector2f(0.f, 2.5f), sf::Vector2f(5.f, 0.5f), 0.f));
	m_staticBlocks.push_back(new StaticBlock(m_pWorld, m_view, sf::Vector2f(-0.5f, -2.f), sf::Vector2f(4.f, 0.2f), -10.f));
	m_staticBlocks.push_back(new StaticBlock(m_pWorld, m_view, sf::Vector2f(1.f, -.5f), sf::Vector2f(5.5f, 0.2f), 10.f));
	m_staticBlocks.push_back(new StaticBlock(m_pWorld, m_view, sf::Vector2f(3.8f, -1.6f), sf::Vector2f(0.2f, 1.f), 10.f));
	m_staticBlocks.push_back(new StaticBlock(m_pWorld, m_view, sf::Vector2f(-3.f, 1.f), sf::Vector2f(2.5f, 0.2f), -25.f));

	m_dynamicBlocks.push_back(new DynamicBlock(m_pWorld, m_view, sf::Vector2f(-1.f, 2.f), sf::Vector2f(0.1f, 0.5f), 0.f));
	m_dynamicBlocks.push_back(new DynamicBlock(m_pWorld, m_view, sf::Vector2f(-0.7f, 2.f), sf::Vector2f(0.1f, 0.5f), 0.f));
	m_dynamicBlocks.push_back(new DynamicBlock(m_pWorld, m_view, sf::Vector2f(-0.85f, 1.7f), sf::Vector2f(0.5f, 0.1f), 0.f));

	m_balls.push_back(new DynamicCircle(m_pWorld, m_view, sf::Vector2f(-1.5f, -3.f), 0.15f, 0.f));
	m_balls.push_back(new DynamicCircle(m_pWorld, m_view, sf::Vector2f(-0.85f, 1.6f), 0.1f, 0.f));

	// Comment to remove effect of contact listener
	m_pWorld->SetContactListener(&m_contactListner);
}

Game::~Game()
{
	// Clean up all pointers
	for each (StaticBlock* block in m_staticBlocks)
	{
		delete block;
		block = nullptr;
	}

	for each (DynamicBlock* block in m_dynamicBlocks)
	{
		delete block;
		block = nullptr;
	}

	for each (DynamicCircle* ball in m_balls)
	{
		delete ball;
		ball = nullptr;
	}

	delete m_pWorld;
	m_pWorld = nullptr;
}

void Game::update(float timestep)
{
	// Update the world
	m_pWorld->Step(timestep, mk_iVelIterations, mk_iVelIterations);

	// Update each dyanmic element - effectively update render information
	for each (DynamicBlock* block in m_dynamicBlocks) block->update();
	for each (DynamicCircle* ball in m_balls) ball->update();
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// Set the view
	target.setView(m_view);

	// Draw everything
	for each (StaticBlock* block in m_staticBlocks) target.draw(*block);
	for each (DynamicBlock* block in m_dynamicBlocks) target.draw(*block);
	for each (DynamicCircle* ball in m_balls) target.draw(*ball);
}

