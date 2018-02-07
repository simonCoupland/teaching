#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <vector>

class Background : public sf::Drawable
{
private :
	sf::Color backgroundColourTop;
	sf::Color backgroundColourBottom;
	std::vector<sf::Texture>::iterator starTexture;
	std::vector<sf::Texture>::iterator moonTexture;
	std::vector<sf::Sprite> stars;
	std::vector<sf::Sprite> moons;
public :
	Background();
	void setColours(sf::Color top,sf::Color bottom); 
	void setStar(std::vector<sf::Texture>::iterator s);
	void setMoon(std::vector<sf::Texture>::iterator m);
	void initialise();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif