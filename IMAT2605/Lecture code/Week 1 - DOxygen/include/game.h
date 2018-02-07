/**
@file game.h
*/

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "textureLoader.h"
#include "ball.h"
#include "OBB.h"
#include "paddle.h"
#include "bumper.h"

class Game : public sf::Drawable
{
private:
	TextureLoader * pm_textureLoader; //!< Class which contains all the textures
	sf::Sprite m_backgroundSprite; //!< Background sprite of the game
	Ball m_ball;
	std::vector<OBB> m_obbs;
	Paddle m_leftPaddle;
	Paddle m_rightPaddle;
	std::vector<Bumper> m_bumpers;
	bool m_leftPaddleActive;
	bool m_rightPaddleActive;
	bool m_springActive;
public:
	Game(); //!< Constructor
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw function (from sf::Drawable)
	void update(float timestep); //!< Update all entities in the game
	void processKeyPress(sf::Keyboard::Key code); //!< Action any key presses
	void processKeyRelease(sf::Keyboard::Key code); //!< Action any key releases
};

#endif