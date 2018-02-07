/**
@file main.cpp
*/

/*! \mainpage Ball Falling - Not OO
 */

#include <SFML/Graphics.hpp>

// Ball data
sf::Vector2f ballPosition; //!< Position of the ball in 2D space
sf::Vector2f ballVelocity; //!< Velocity of the ball
sf::Vector2f ballAcceleration; //!< Acceleration acting on the ball
float fBallRadius; //!< Radius of the ball
int iBallNumPoints; //!< Number of points used to draw the ball

// Functions used to manipulate the balls data
void initialiseBall(); //!<  Set initial values for the balls data
void updateBallPhysics(float fTimestep); //!<  Update the balls properties over a timestep

// Horizontal line Data
float fLinePos; //!< Position of the line in y
float fLineWidth; //!< Width of the line in y

// Functions used to manipulate the lines data
void initialiseLine(); //!<  Set initial values for the line data

// Drawing functions
void drawBall(); //!<  Draws the ball
void drawLine(); //!<  Draws the line

// Window
sf::RenderWindow * window; //!< SFML Render window

/*! Entry point for the application */
int main() 
{
	// Set up objects in our scene
	initialiseBall();
	initialiseLine();

	// Set up a window
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Non OO"); // Open main window

	// Start a clock to provide time for the physics
	sf::Clock clock;

	// Enter a ongoing loop
	while (window->isOpen())
    {
		window->clear(sf::Color::White);

        sf::Event event;
        while (window->pollEvent(event))
        {
			// window closed button pressed
            if (event.type == sf::Event::Closed)
                window->close();
        }
		
		// Find out how much time has elapsed
		float fElapsedTime = clock.getElapsedTime().asSeconds();
		// If a frame has past the update the physics
		if(fElapsedTime > 0.01)
		{
			updateBallPhysics(fElapsedTime);
			clock.restart();
		}
	
		// Draw line and ball
		drawBall();
		drawLine();
		// Render the window
		window->display();
    }

	delete window;

	return 0;
}

void initialiseBall()
{
	ballPosition.x = 25.0f;
	ballPosition.y = 50.0f;

	ballVelocity.x = 60.0f;
	ballVelocity.y = 0.0f;

	ballAcceleration.x = 0.0f;
	ballAcceleration.y = 100.0f;

	fBallRadius = 35.0f;

	iBallNumPoints = 60;
}

void updateBallPhysics(float fTimestep) 
{
	// Update velocity and position use Euler
	ballVelocity = ballVelocity + ballAcceleration * fTimestep;
	ballPosition = ballPosition + ballVelocity * fTimestep;

	// Check for a collision
	if(ballPosition.y + fBallRadius > fLinePos)
	{
		// Ball has gone below the line
		ballPosition.y = fLinePos-fBallRadius;
		ballVelocity.y = -ballVelocity.y * 0.8;
	}
}

void initialiseLine() 
{
	fLinePos = 560.0f;
	fLineWidth = 800.0f;
}

void drawBall() 
{
	sf::VertexArray circle(sf::LinesStrip, iBallNumPoints+1);
	float ft = 0.0f;
	float fdetlaT = 6.28319 / (float)(iBallNumPoints-1);
	float fx,fy;
	
	for(int i=0;i < iBallNumPoints+1;i++)
	{
		fx = cos(ft) * fBallRadius;
		fy = sin(ft) * fBallRadius;
		ft = ft + fdetlaT;
		circle[i] = sf::Vertex(sf::Vector2f(ballPosition.x + fx,ballPosition.y + fy),sf::Color::Blue);
	}

	window->draw(circle);
}

void drawLine() 
{
	sf::VertexArray line(sf::Lines, 2);
	line[0] = sf::Vertex(sf::Vector2f(0,fLinePos),sf::Color::Black);
	line[1] = sf::Vertex(sf::Vector2f(fLineWidth,fLinePos),sf::Color::Black);

	window->draw(line);
}