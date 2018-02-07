/**
@file main.cpp
*/

/*! \mainpage Ball Falling - Object Oriented Version
 */

#include <SFML/Graphics.hpp>

#include "ball.h"
#include "line.h"

void main() /** Entry point for the application */
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "OO Version"); // Open main window
	
	Ball myBall(25.0f, 50.0f, 60.0f, 0.0f); // Create a ball object
	Line myLine(560.0f, 800.0f); // Create a line object

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
		if(fElapsedTime > 0.01)
		{
			myBall.updatePhysics(fElapsedTime, myLine.getPosition());
			clock.restart();
		}
		
		window.draw(myBall);
		window.draw(myLine);


		window.display();
    }

	

}