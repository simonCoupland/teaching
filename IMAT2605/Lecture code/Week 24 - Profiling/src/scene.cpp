/**
@file scene.cpp
*/

#include "scene.h"

Scene::Scene(int wh) //!< Default constructor
{
	view.reset(sf::FloatRect(0.0f,0.0f,400.0f,300.0f));
	view.setCenter(400.0f,450.0f);

	windowHeight = wh;

	scrollBuffer =50.0f;
	scrollAmount = 1.0f;

	textureLoader.setBaseDirectory("C:\\Users\\scoupl00\\Documents\\teaching\\IMAT2605\\2017\\Lecture Demos\\Lecture 24 - Profiling\\assets\\textures\\");
	std::string fileNames[4] = {"star.png","moon.png","ball.png","tile.png"};
	textureLoader.load(std::vector<std::string>(std::begin(fileNames),std::end(fileNames)));
	
	background.setColours(sf::Color(50,0,95),sf::Color::White);
	background.setStar(textureLoader.getTextureIterator(0));
	background.setMoon(textureLoader.getTextureIterator(1));
	background.initialise();
	
	balls.push_back(Ball(windowHeight, 10.0f, Vector2D(340,180),Vector2D(12,-40),Vector2D(0,-10),0.0f,3.0f,textureLoader.getTextureIterator(2),0.1f, 1.0f, 0.05f));
	balls.push_back(Ball(windowHeight, 18.0f, Vector2D(450,200),Vector2D(-6,-10),Vector2D(0,-10),0.0f,2.0f,textureLoader.getTextureIterator(2),0.1f, 1.0f, 0.05f));

	for(int i=0;i<40;i++)
	{
		if(i%2) platforms.push_back(Box(windowHeight, Vector2D(10.0f,10.0f), Vector2D(i+i*20,30),Vector2D(0,0),Vector2D(0,-10),textureLoader.getTextureIterator(3),0.05f));
		else platforms.push_back(Box(windowHeight, Vector2D(10.0f,10.0f), Vector2D(i+i*20,40),Vector2D(0,0),Vector2D(0,-10),textureLoader.getTextureIterator(3),0.05f));
	}

	for(int i=0;i<5;i++)
	{
		if(i%2) platforms.push_back(Box(windowHeight, Vector2D(10.0f,10.0f), Vector2D(0, i+i*20+61),Vector2D(0,0),Vector2D(0,-10),textureLoader.getTextureIterator(3),0.05f));
		else platforms.push_back(Box(windowHeight, Vector2D(10.0f,10.0f), Vector2D(10, i+i*20+61),Vector2D(0,0),Vector2D(0,-10),textureLoader.getTextureIterator(3),0.05f));
	}

	for(int i=0;i<5;i++)
	{
		if(i%2) platforms.push_back(Box(windowHeight, Vector2D(10.0f,10.0f), Vector2D(800, i+i*20+61),Vector2D(0,0),Vector2D(0,-10),textureLoader.getTextureIterator(3),0.05f));
		else platforms.push_back(Box(windowHeight, Vector2D(10.0f,10.0f), Vector2D(790, i+i*20+61),Vector2D(0,0),Vector2D(0,-10),textureLoader.getTextureIterator(3),0.05f));
	}
}

void Scene::update(float time) //!< Move the scene along 
{
	// Clamp time for debugging
	time = std::min(time,0.01f);
	std::vector<Box>::iterator platformIt;
	std::vector<Ball>::iterator ballIt, ballIt2;

	// Update moving balls
	for(ballIt = balls.begin(); ballIt != balls.end(); ++ballIt)
	{
		ballIt->integrate(time);
	}

	Vector2D normal; // Collision normal
	Vector2D contactVectorA, contactVectorB; // Vector between COM and contact point
	float penetration; // Amount one shape and penetrated another

	// Check balls against platforms
	for(platformIt = platforms.begin(); platformIt != platforms.end(); ++platformIt)
	{
		for(ballIt = balls.begin(); ballIt != balls.end(); ++ballIt)
		{
			if(collisionHelper.AABBvsCIRCLE(*platformIt, *ballIt,penetration,normal,contactVectorA,contactVectorB)) 
			{
				collisionHelper.PositionCorrection(*platformIt,*ballIt,penetration,normal,2.0f,1.0f);
				collisionHelper.ResolveWithRotation(*platformIt,*ballIt,normal,contactVectorA,contactVectorB);
			}
		}
	}

	// Check balls against balls
	for(ballIt2 = balls.begin(); ballIt2 != balls.end(); ++ballIt2)
	{
		for(ballIt = ballIt2; ballIt != balls.end(); ++ballIt)
		{
			if(ballIt2 != ballIt)
			{
				if(collisionHelper.CIRCLEvsCIRCLE(*ballIt2, *ballIt,penetration,normal,contactVectorA,contactVectorB)) 
				{
					collisionHelper.PositionCorrection(*ballIt2,*ballIt,penetration,normal,0.5f,2.0f);
					collisionHelper.ResolveWithRotation(*ballIt2,*ballIt,normal,contactVectorA,contactVectorB);
				}
			}
		}
	}

	// Update render positions
	for(ballIt = balls.begin(); ballIt != balls.end(); ++ballIt)
	{
		ballIt->update();
	}
	for(platformIt = platforms.begin(); platformIt != platforms.end(); ++platformIt)
	{
		platformIt->update();
	}

	// Move view
	float centre = view.getCenter().x;
	float halfWidth = view.getSize().y / 2.0f;

	if(centre + halfWidth - scrollBuffer < balls[1].centreX())
	{
		// Move right
		centre = centre + scrollAmount;
		view.setCenter(sf::Vector2f(centre,view.getCenter().y));
	}
	else if(centre - halfWidth + scrollBuffer > balls[1].centreX())
	{
		// Move left
		centre = centre - scrollAmount;
		view.setCenter(sf::Vector2f(centre,view.getCenter().y));
	}
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::vector<Box>::const_iterator boxIt;
	std::vector<Ball>::const_iterator ballIt;

	target.setView(view);

	target.draw(background);


	for(boxIt = platforms.cbegin(); boxIt != platforms.cend(); ++boxIt)
	{
		target.draw(*boxIt);
	}

	for(ballIt = balls.cbegin(); ballIt != balls.cend(); ++ballIt)
	{
		target.draw(*ballIt);
	}
}
