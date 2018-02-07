#include "line.h"

Line::Line(float fPos, float fWid)
{
	fPosition = fPos;
	fWidth = fWid;
}

void Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray line(sf::Lines, 2);
	line[0] = sf::Vertex(sf::Vector2f(0,fPosition),sf::Color::Black);
	line[1] = sf::Vertex(sf::Vector2f(fWidth,fPosition),sf::Color::Black);

	target.draw(line);
}

float Line::getPosition()
{
	return fPosition;
}
