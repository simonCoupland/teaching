#ifndef BOX_H
#define BOX_H

#include <SFML/Graphics.hpp>

#include "movable.h"
#include "collidable.h"

class Box : public Collidable, public sf::Drawable
{
private:
	Vector2D extents;
	sf::Sprite sprite;
	virtual float area();
	int windowHeight;
public:
	Box(int wh, Vector2D &e, Vector2D &r, Vector2D &v, Vector2D &a, float th, float w, std::vector<sf::Texture>::iterator texIter, float d, float ce, float cf);
	Box(int wh, Vector2D &e, Vector2D &r, Vector2D &v, Vector2D &a, std::vector<sf::Texture>::iterator texIter, float cf);
	virtual Vector2D accelerationFunction(Vector2D &v);
	virtual float angularAccelerationFunction(float &w);
	void update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	friend class Collisions;
};

#endif