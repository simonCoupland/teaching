/**
@file main.cpp
*/

#include <SFML/Graphics.hpp>

#include "scene.h"


int main() /** Entry point for the application */
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Drawing Demo", sf::Style::Default, settings); // Open main window

	Scene myScene(600);

	sf::Clock timer; // Creates and starts a timer
	sf::Time elapsed; // Time elapsed during frame

	// Run a game loop
	while (window.isOpen())
    {
		window.clear(sf::Color::White);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
				window.close();
        }

		if(timer.getElapsedTime().asSeconds() > 0.025f) // Only update 40 times a second
		{
			elapsed = timer.restart();
			myScene.update(elapsed.asSeconds());
		}


		window.draw(myScene);

		window.display();
    }

	return 0;
}