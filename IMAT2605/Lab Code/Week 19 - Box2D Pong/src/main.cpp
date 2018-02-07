/*!
\file main.cpp
\brief Contains the entry point for the application
*/

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

void main() /** Entry point for the application */
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D Pong"); // Open main window

	float fFrameTime = 1.f / 60.f;

	// Start a clock to provide time for the physics
	sf::Clock clock;

	// Set the view, so we see (0,0) to (8,6)
	sf::Vector2f worldSize(8.0f, 6.0f); // World is 8 x 6 metres (good size for box 2D
	
	sf::View gameView;
	gameView.setCenter(4.f, 3.f);
	gameView.setSize(worldSize.x, worldSize.y);

	window.setView(gameView);

	// Set up some shapes to display

	sf::RectangleShape topWall;
	topWall.setSize(sf::Vector2f(8.f, 0.1f));
	topWall.setPosition(0.f, 0.f);
	topWall.setFillColor(sf::Color::Blue);

	sf::RectangleShape bottomWall;
	bottomWall.setSize(sf::Vector2f(8.f, 0.1f));
	bottomWall.setPosition(0.f, 5.9f);
	bottomWall.setFillColor(sf::Color::Blue);

	sf::CircleShape ball;
	ball.setRadius(0.15f);
	ball.setPosition(4.f, 3.f);
	ball.setFillColor(sf::Color::Red);
	ball.setOrigin(0.15f, 0.15f);

	// Set up the box2D world
	b2World * world = new b2World(b2Vec2(0.f, 0.f));

	// Some physical properties, everything can have the same for now
	const float fDensity = 1.0f; //!< Density of the material - used to give mass
	const float fFriction = 0.f; //!< Friction - I guess this is only friction from movement, not when static
	const float fRestitution = 1.0f; //1< Restitution - bouncyness of stuff

	b2Body * topWallBody;
	b2Body * bottomWallBody;
	b2Body * ballBody;

	// Set up static bodies

	b2BodyDef bodyDef;
	b2PolygonShape boxShape;
	b2CircleShape circleShape;
	b2FixtureDef fixtureDef;

	fixtureDef.density = fDensity;
	fixtureDef.friction = fFriction;
	fixtureDef.restitution = fRestitution;

	// Top wall
	bodyDef.position.Set(topWall.getPosition().x, topWall.getPosition().y);
	bodyDef.angle = 0.f;

	topWallBody = world->CreateBody(&bodyDef);

	boxShape.SetAsBox(topWall.getSize().x * 0.5f, topWall.getSize().y * 0.5f);
	boxShape.m_radius = 0.0f;

	fixtureDef.shape = &boxShape;

	topWallBody->CreateFixture(&fixtureDef);

	// Bottom wall
	bodyDef.position.Set(bottomWall.getPosition().x, bottomWall.getPosition().y);
	bodyDef.angle = 0.f;

	bottomWallBody = world->CreateBody(&bodyDef);

	boxShape.SetAsBox(bottomWall.getSize().x * 0.5f, bottomWall.getSize().y * 0.5f);
	boxShape.m_radius = 0.0f;

	fixtureDef.shape = &boxShape;

	bottomWallBody->CreateFixture(&fixtureDef);

	// Ball

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(ball.getPosition().x, ball.getPosition().y);
	bodyDef.linearVelocity = b2Vec2(0.f, -2.5f); // give the ball some initial velocity


	ballBody = world->CreateBody(&bodyDef);

	circleShape.m_radius = ball.getRadius();

	fixtureDef.density = fDensity;
	fixtureDef.friction = fFriction;
	fixtureDef.restitution = fRestitution;
	fixtureDef.shape = &circleShape;

	ballBody->CreateFixture(&fixtureDef);

	// Run a game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// window closed button pressed
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Find out how much time has elapsed

		float fElapsedTime = clock.getElapsedTime().asSeconds();
		// If a frame has past...
		if (fElapsedTime > fFrameTime)
		{
			world->Step(fElapsedTime, 7, 5);

			// Update the ball position
			b2Vec2 pos = ballBody->GetPosition();
			ball.setPosition(pos.x, pos.y);

			clock.restart();
		}

		window.clear(sf::Color::White);

		window.draw(topWall);
		window.draw(bottomWall);
		window.draw(ball);

		window.display();
	}



}