#include "background.h"

Background::Background()
{
}

void Background::setColours(sf::Color top,sf::Color bottom)
{
	backgroundColourTop = top;
	backgroundColourBottom = bottom;
}

void Background::setStar(std::vector<sf::Texture>::iterator s)
{
	starTexture = s;
}

void Background::setMoon(std::vector<sf::Texture>::iterator m)
{
	moonTexture = m;
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::vector<sf::Sprite>::const_iterator c_itr;

	sf::VertexArray clearRect(sf::Quads,4);
	sf::Vertex v;

	v.color = backgroundColourBottom;
	v.position = sf::Vector2f(-100,target.getSize().y);
	clearRect[0] = v;

	v.position = sf::Vector2f(900,target.getSize().y);
	clearRect[1] = v;

	v.color = backgroundColourTop;
	v.position = sf::Vector2f(900,target.getSize().y/2.0);
	clearRect[2] = v;

	v.position = sf::Vector2f(-100,target.getSize().y/2.0);
	clearRect[3] = v;

	target.draw(clearRect);

	for(c_itr = stars.cbegin(); c_itr != stars.end(); ++c_itr)
	{
		target.draw(*c_itr);
	}

	for(c_itr = moons.cbegin(); c_itr != moons.end(); ++c_itr)
	{
		target.draw(*c_itr);
	}
}

void Background::initialise()
{
	sf::Sprite starSprite(*starTexture);

	starSprite.setScale(0.4,0.4);
	starSprite.setPosition(40,320);
	starSprite.setRotation(-10);
	stars.push_back(starSprite);

	starSprite.setScale(0.3,0.3);
	starSprite.setPosition(310,310);
	starSprite.setRotation(25);
	stars.push_back(starSprite);

	starSprite.setScale(0.25,0.25);
	starSprite.setPosition(10,370);
	starSprite.setRotation(15);
	stars.push_back(starSprite);

	starSprite.setScale(0.4,0.4);
	starSprite.setPosition(510,320);
	starSprite.setRotation(40);
	stars.push_back(starSprite);

	starSprite.setScale(0.3,0.3);
	starSprite.setPosition(610,360);
	starSprite.setRotation(-15);
	stars.push_back(starSprite);

	starSprite.setScale(0.25,0.25);
	starSprite.setPosition(710,310);
	starSprite.setRotation(-20);
	stars.push_back(starSprite);

	sf::Sprite moonSprite(*moonTexture);
	
	moonSprite.setScale(0.4,0.4);
	moonSprite.setPosition(180,460);
	moonSprite.setRotation(220);
	moons.push_back(moonSprite);

	moonSprite.setScale(0.2,0.2);
	moonSprite.setPosition(210,310);
	moonSprite.setRotation(-30);
	moons.push_back(moonSprite);

	moonSprite.setScale(0.25,0.25);
	moonSprite.setPosition(330,440);
	moonSprite.setRotation(-90);
	moons.push_back(moonSprite);

	moonSprite.setScale(0.4,0.4);
	moonSprite.setPosition(400,310);
	moonSprite.setRotation(15);
	moons.push_back(moonSprite);

	moonSprite.setScale(0.2,0.2);
	moonSprite.setPosition(580,360);
	moonSprite.setRotation(215);
	moons.push_back(moonSprite);

	moonSprite.setScale(0.25,0.25);
	moonSprite.setPosition(765,360);
	moonSprite.setRotation(70);
	moons.push_back(moonSprite);
}

