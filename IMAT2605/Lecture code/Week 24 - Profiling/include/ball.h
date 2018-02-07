#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

#include "movable.h"
#include "collidable.h"

class Ball : public Collidable, public sf::Drawable
{
private:
	float radius;
	sf::Sprite sprite;
	virtual float area();
	int windowHeight;
public:
	Ball(int wh, float rad, Vector2D &r, Vector2D &v, Vector2D &a, float th, float w, std::vector<sf::Texture>::iterator texIter, float d, float ce, float cf);
	Ball(int wh, float rad, Vector2D &r, Vector2D &v, Vector2D &a, float th, float w, std::vector<sf::Texture>::iterator texIter, float cf);
	virtual Vector2D accelerationFunction(Vector2D &v);
	virtual float angularAccelerationFunction(float &w);
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float centreX();
	friend class Collisions;
};

#endif