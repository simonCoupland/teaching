#ifndef GAME_H
#define GAME_H

#include <array>

#include "paddle.h"
#include "staticObject.h"
#include "movingObject.h"

using namespace std;

class Game : public Drawable
{
private:
	Paddle m_paddle;
	Paddle m_aiPaddle;
	MovingObject m_ball;
	array<StaticObject, 4> m_aStaticObjects;
	Vector2f m_ballStartPosition;
public:
	Game();
	void update(float time);
	void draw(RenderTarget& target, RenderStates states) const;
	void processEvent(Event& e);
};

#endif