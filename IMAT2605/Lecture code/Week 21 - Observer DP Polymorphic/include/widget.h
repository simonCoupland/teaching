#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>
#include <sstream>

#include "MouseClickObserver.h"

class Widget : public MouseClickObserver, public sf::Text
{
private:
	string a_sButtonText[3];
	sf::Font arial;
public:
	Widget();
	void update(MouseClickEvent state);
};

#endif