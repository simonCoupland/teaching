#ifndef GAME_H
#define GAME_H

#include <array>

#include "character.h"
#include "staticObject.h"
#include "movingObject.h"

using namespace std;

class Game : public Drawable
{
private:
	Character m_character;
	array<StaticObject, 5> m_aStaticObjects;
	array<MovingObject, 8> m_aCrashingObjects;
	array<MovingObject, 8> m_aCarryingObjects;
	Vector2f characterStartPosition;
public:
	Game();
	void update(float time);
	void draw(RenderTarget& target, RenderStates states) const;
	void processEvent(Event& e);
};

#endif