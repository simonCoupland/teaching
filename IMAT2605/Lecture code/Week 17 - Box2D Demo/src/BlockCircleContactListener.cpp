#include "BlockCircleContactListener.h"

void BlockCircleContactListener::BeginContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	b2BodyType typeA = bodyA->GetType();
	b2BodyType typeB = bodyA->GetType();

	b2Shape::Type shapeA = bodyA->GetFixtureList()->GetShape()->GetType();
	b2Shape::Type shapeB = bodyB->GetFixtureList()->GetShape()->GetType();

	if (shapeA == b2Shape::Type::e_circle && typeB == b2BodyType::b2_staticBody)
	{
		StaticBlock * block = static_cast<StaticBlock*>(bodyB->GetUserData());
		if (block != nullptr) block->setFillColor(sf::Color::Magenta);
	}

	if (shapeB == b2Shape::Type::e_circle && typeA == b2BodyType::b2_staticBody)
	{
		StaticBlock * block = static_cast<StaticBlock*>(bodyA->GetUserData());
		if (block != nullptr) block->setFillColor(sf::Color::Magenta);
	}

	if (typeA == b2BodyType::b2_dynamicBody && shapeB == b2Shape::Type::e_circle)
	{
		DynamicBlock * block = static_cast<DynamicBlock*>(bodyA->GetUserData());
		if (block != nullptr) block->setFillColor(sf::Color::Cyan);
	}

	if (typeB == b2BodyType::b2_dynamicBody && shapeA == b2Shape::Type::e_circle)
	{
		DynamicBlock * block = static_cast<DynamicBlock*>(bodyB->GetUserData());
		if (block != nullptr) block->setFillColor(sf::Color::Cyan);
	}
}

void BlockCircleContactListener::EndContact(b2Contact * contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	b2BodyType typeA = bodyA->GetType();
	b2BodyType typeB = bodyA->GetType();

	b2Shape::Type shapeA = bodyA->GetFixtureList()->GetShape()->GetType();
	b2Shape::Type shapeB = bodyB->GetFixtureList()->GetShape()->GetType();

	if (shapeA == b2Shape::Type::e_circle && typeB == b2BodyType::b2_staticBody)
	{
		StaticBlock * block = static_cast<StaticBlock*>(bodyB->GetUserData());
		if (block != nullptr) block->setFillColor(sf::Color::Green);
	}

	if (shapeB == b2Shape::Type::e_circle && typeA == b2BodyType::b2_staticBody)
	{
		StaticBlock * block = static_cast<StaticBlock*>(bodyA->GetUserData());
		if (block != nullptr) block->setFillColor(sf::Color::Green);
	}

	if (typeA == b2BodyType::b2_dynamicBody && shapeB == b2Shape::Type::e_circle)
	{
		DynamicBlock * block = static_cast<DynamicBlock*>(bodyA->GetUserData());
		if (block != nullptr) block->setFillColor(sf::Color::Red);
	}

	if (typeB == b2BodyType::b2_dynamicBody && shapeA == b2Shape::Type::e_circle)
	{
		DynamicBlock * block = static_cast<DynamicBlock*>(bodyB->GetUserData());
		if (block != nullptr) block->setFillColor(sf::Color::Red);
	}
}
