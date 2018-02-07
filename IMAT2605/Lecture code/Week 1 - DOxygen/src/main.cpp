/**
@file main.cpp
*/

/*! \mainpage Pinball Demo
 */

#include <SFML/Graphics.hpp>

#include "game.h"

void main() /** Entry point for the application */
{
    sf::RenderWindow window(sf::VideoMode(450, 600), "Pinball"); // Open main window

	Game game; // Pinball game object

	sf::Clock clock; // Game time clock
	
	// Run a game loop
	while (window.isOpen())
    {
		window.clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
			// window closed button pressed
            if (event.type == sf::Event::Closed)
                window.close();
			// keypress
			if(event.type == sf::Event::KeyPressed)
				game.processKeyPress(event.key.code);
			// keyrelease
			if(event.type == sf::Event::KeyReleased)
				game.processKeyRelease(event.key.code);
        }

		// Get the elasped time during the frame

		if(clock.getElapsedTime().asSeconds() > 0.005)
		{
			game.update(clock.getElapsedTime().asSeconds());
			clock.restart();
		}

		window.draw(game);
		
		window.display();
    }

	

}

