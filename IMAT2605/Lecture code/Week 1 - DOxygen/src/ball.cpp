/**
@file ball.cpp
*/

#include "ball.h"

Ball::Ball()
{
	/*
int age; // A persons age
float height; // A persons height in metres
//char gender; // A person gender M or F
bool footballFan; // Is the person a football fan

age = 34;
height = 1.82;
//gender = 'M';
footballFan = true;


int salary;
int doubleSalary;
int tripleSalary;
int quadrupleSalary;

salary = 22000;
tripleSalary = salary * 3; // 66000
doubleSalary = tripleSalary - salary; // 44000
quadrupleSalary = doubleSalary + doubleSalary; // 88000


float speed;
float time;
float distance;

speed = 25.65;
time = 3.8;

speed = distance / time; // 6.75

int numberOfApples;
int numberOfPeople;
int numberOfApplesEach;
int numberOfApplesLeft;

numberOfApples = 11;
numberOfPeople = 3;

numberOfApplesEach = numberOfApples / numberOfPeople; // 3
numberOfApplesLeft =  numberOfApples % numberOfPeople; // 2 

int count;

count = 0;
count = count + 1; // 1
count++; // 2
count--; // 1

float initialSpeed = 25.0;
float finalSpeed = 75.0;
float averageSpeed1 = initialSpeed + finalSpeed / 2; // ?
float averageSpeed2 = (initialSpeed + finalSpeed) / 2; // ?	

float angle1 = 45; // 45.0
int angle2 = angle1 * 4; // 180
int angle3 = int(angle1) * 4; // 180
int sum = 12.0; // 12
int count = 32.0; // 32
float average = float(sum) / float(count); // 0.375

enum gender {male, female, notGiven};
gender myGender = male;
*/

	// Load textures
	TextureLoader * pm_textureLoader = pm_textureLoader->instance();

	// Set the texture for the ball
	m_ballSprite.setTexture(* pm_textureLoader->getTexture(1));
	m_ballSprite.setOrigin(15.f,15.f);
	
	// Set the radius
	m_fRadius = 15.0f;

	// Set the coefficient of elasticity
	m_fCoeffElasticity = 0.95;

	// Set the initial position
	m_position.set(410.f, 530.f);

	// Set the initial velocity
	m_velocity.set(0.f,-0.f);

	// Set the acceleration
	m_acceleration.set(0.f, 75.f);

	// Move the sprite
	m_ballSprite.setPosition(m_position.x(), m_position.y());
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_ballSprite);
}

void Ball::update(float p_timestep)
{
	// Basic Euler
	m_velocity = m_velocity + (m_acceleration * p_timestep);
	m_position = m_position + (m_velocity * p_timestep);

	// Move the sprite
	m_ballSprite.setPosition(m_position.x(), m_position.y());
}

float Ball::getRadius() 
{
	return m_fRadius;
}

Vector2D Ball::getPosition() 
{
	return m_position;
}


float Ball::getCoeffElasticity()
{
	return m_fCoeffElasticity;
}

void Ball::fire()
{
	m_velocity.set(0.f,-800.f);
}

void Ball::resolveStaticCollision(Vector2D collisionNormal, float coeffElasticity)
{
	// Calculate relative velocity along the normal
	float velAlongNormal = m_velocity.dotProduct(collisionNormal);
 
	// Do not resolve if velocities are separating
	if(velAlongNormal > 0)
	return;
 
	// Calculate impulse scalar
	float j =  -(1.0f + coeffElasticity) * velAlongNormal;

	// Apply impulse
	Vector2D impulse = collisionNormal * j;
	m_velocity = m_velocity + impulse;
}


void Ball::resolveDynamicCollision(Vector2D collisionNormal, float velocity, float coeffElasticity)
{
	// Calculate relative velocity along the normal
	float velAlongNormal = (m_velocity - (collisionNormal * velocity)).dotProduct(collisionNormal);

	// Do not resolve if velocities are separating
	if(velAlongNormal > 0)
	return;
 
	// Calculate impulse scalar
	float j =  -(1.0f + coeffElasticity) * velAlongNormal;

	// Apply impulse
	Vector2D impulse = collisionNormal * j;
	m_velocity = m_velocity + impulse;
}