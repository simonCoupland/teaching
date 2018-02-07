#include <SFML/Graphics.hpp>

#include "game.h"

using namespace sf;

void main()
{
	RenderWindow window(VideoMode(800, 600), "OO Pong V1");

	// Create a game object
	Game game;

	// Start a clock to provide time for the physics
	Clock clock;

	// Run a game loop
	while (window.isOpen())
	{
		// Clear the background
		window.clear(Color::White);

		Event event;
		while (window.pollEvent(event))
		{
			// window closed button pressed
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else
			{
				game.processEvent(event);
			}
		}

		// Find out how much time has elapsed
		float fElapsedTime = clock.getElapsedTime().asSeconds();
		// If a frame has past the update the physics
		if (fElapsedTime > 0.01)
		{
			game.update(fElapsedTime);
			clock.restart();
		}

		window.draw(game);

		window.display();
	}



}