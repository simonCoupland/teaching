#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>

/*! A line Class */
class Line : public sf::Drawable
{
private:
	float fPosition; //!< Position of the line in y
	float fWidth; //!< Width of the line in y
public:
	Line(float fPos, float fWid); //!< Constructor which takes position and width
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Draw the line
	float getPosition(); //!< Returns the position of the line
};

#endif