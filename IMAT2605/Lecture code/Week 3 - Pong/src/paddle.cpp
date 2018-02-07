#include "paddle.h"

Paddle::Paddle(Vector2f& position, Vector2f& dimensions, Color& color)
{
	setPosition(position);
	setSize(dimensions);
	setOrigin(dimensions.x / 2.f, dimensions.y / 2.f);
	setFillColor(color);
}

void Paddle::processEvent(Event& e)
{
	if (e.type == Event::KeyPressed)
	{
		if (e.key.code == Keyboard::Up)
		{
			move(0.f, -10.f);
		}
		if (e.key.code == Keyboard::Down)
		{
			move(0.f, 10.f);
		}
	}
}