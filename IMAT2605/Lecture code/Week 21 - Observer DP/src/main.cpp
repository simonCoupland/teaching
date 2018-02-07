

#include <SFML/Graphics.hpp>
#include <memory.h>
#include "mouseClickSubscriber.h"
#include "mouseClickObserver.h"


using namespace std;

void main() /** Entry point for the application */
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Observer Pattern Demo"); // Open main window

	MouseClickSubscriber mouseSubscriber;
	
	MouseClickObserver logger1;
	MouseClickObserver logger2;

	mouseSubscriber.attach(&logger1);
	mouseSubscriber.attach(&logger2);

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
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
				{
					mouseSubscriber.notify(MouseClickEvent(MouseClickEvent::left, event.mouseButton.x, event.mouseButton.y));
				}
				if(event.mouseButton.button == sf::Mouse::Right)
				{
					mouseSubscriber.notify(MouseClickEvent(MouseClickEvent::right, event.mouseButton.x, event.mouseButton.y));
				}
				if(event.mouseButton.button == sf::Mouse::Middle)
				{
					mouseSubscriber.notify(MouseClickEvent(MouseClickEvent::wheel, event.mouseButton.x, event.mouseButton.y));
				}
			}
        }

		window.display();
    }

	

}