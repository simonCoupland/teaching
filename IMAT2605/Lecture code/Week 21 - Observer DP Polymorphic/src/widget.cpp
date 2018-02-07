#include "widget.h"

Widget::Widget()
{
	a_sButtonText[0] = "Left";
	a_sButtonText[1] = "Right";
	a_sButtonText[2] = "Wheel";

		// Load Font
		
	arial.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

	setFont(arial);
	setCharacterSize(30);
	setFillColor(sf::Color::White);
	setPosition(100,100);
}

void Widget::update(MouseClickEvent state)
{
	// Move text
	setPosition(state.getX(), state.getY());
	// Set string
	std::stringstream s;
	s << "Mouse button: " << a_sButtonText[state.getButton()];
	s << " x: " << state.getX();
	s << " y: " << state.getY();

	setString(s.str());
}