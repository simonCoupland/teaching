/**
@file scene.h
*/

#ifndef SCENE_H
#define SCENE_H

/*! \class Scene
    \brief An animated scene consisting of some movable objects
*/

#include <SFML/graphics.hpp>
#include <vector>

#include "textureLoader.h"
#include "background.h"
#include "box.h"
#include "ball.h"
#include "collisions.h"

class Scene : public sf::Drawable
{
private:
	TextureLoader textureLoader;
	Background background;
	std::vector<Ball> balls; //!< Moving balls in the scene
	std::vector<Box> platforms; //!< Fixed platforms in the scene
	Collisions collisionHelper; //!< Identifies collision between objects
	int windowHeight;
	sf::View view;
	float scrollBuffer;
	float scrollAmount;
public:
	Scene(int wh); //!< Default constructor
	void update(float time); //!< Move the scene along
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif