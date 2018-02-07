/*!
\file main.cpp
\brief Contains the entry point for the application
*/

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

#include "game.h"

void main() /** Entry point for the application */
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D Demo"); // Open main window
	Game game;

	float fFrameTime = 1.f / 60.f;

    // Start a clock to provide time for the physics
	sf::Clock clock;

	// Run a game loop
	while (window.isOpen())
	{
		window.clear(sf::Color::White);

		sf::Event event;
		while (window.pollEvent(event))
		{
			// window closed button pressed
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Find out how much time has elapsed

		float fElapsedTime = clock.getElapsedTime().asSeconds();
		// If a frame has past the update the physics
		if (fElapsedTime > fFrameTime)
		{
			game.update(fElapsedTime);
			clock.restart();
		}

		window.draw(game);
		window.display();
	}



}