#pragma once

/*!
\file game.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "staticBlock.h"
#include "dynamicBlock.h"
#include "dynamicCircle.h"

#include "BlockCircleContactListener.h"

/*! \class Game
\brief Holds all information about the game, blocks, balls etc and allows updating and rendering.
*/

class Game : public sf::Drawable {
private:
	sf::View m_view; //!< The view maps from physical co-ordinates to rendering co-ordinates
	sf::Vector2f m_worldSize = sf::Vector2f(8.f, 6.f); //!< Size of the physical worlds is 8 X 6 metres

	b2World* m_pWorld = nullptr; //!< Pointer to the Box2D world.  Using pointers as BOX2D has it's own memory management
	const int mk_iVelIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int mk_iPosIterations = 5; //!< On each update there will be 5 position iterations on each update
	const b2Vec2 mk_gravity = b2Vec2(0.f, -9.81f); //!< Standard earth gravity will be used

	std::vector<StaticBlock *> m_staticBlocks; //!< A collection of fixed blocks. Using pointers to allow polymorphic calls.
	std::vector<DynamicBlock *> m_dynamicBlocks; //!< A collection of moving blocks. Using pointers to allow polymorphic calls.
	std::vector<DynamicCircle* > m_balls; //!< A collection of moving balls. Using pointers to allow polymorphic calls.

	BlockCircleContactListener m_contactListner; //!< A contact listern used for demo purposes
public:
	Game(); //!< Constructor which sets up the game
	~Game(); //!< Destructor which cleans all the pointer memory up
	void update(float timestep); //!< Update the game with give timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the game to the render context
};
