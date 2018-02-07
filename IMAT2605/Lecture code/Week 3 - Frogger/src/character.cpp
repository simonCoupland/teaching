#include "character.h"

Character::Character(Vector2f& position, Vector2f& dimensions, Color& color)
{
	m_velocity = Vector2f(0.f,0.f);
	setPosition(position);
	setSize(dimensions);
	setOrigin(dimensions.x / 2.f, dimensions.y / 2.f);
	setFillColor(color);
}

void Character::processEvent(Event& e)
{
	if (e.type == Event::KeyPressed)
	{
		switch (e.key.code)
		{
		case Keyboard::Up :
			move(Vector2f(0.f,-getSize().y));
			break;
		case Keyboard::Down:
			move(Vector2f(0.f, getSize().y));
			break;
		case Keyboard::Left:
			move(Vector2f(-getSize().x,0.f));
			break;
		case Keyboard::Right:
			move(Vector2f(getSize().x,0.f));
			break;
		default:
			break;
		}
	}
}

void Character::setVelocity(Vector2f& velocity)
{
	m_velocity = velocity;
}