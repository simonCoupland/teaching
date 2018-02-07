/**
@file vector2D.cpp
*/

#include "vector2D.h"

Vector2D::Vector2D()  //!< Default consturct, set everything to zero
{
	data[0] = 0;
	data[1] = 0;
}

Vector2D::Vector2D(float allValues) //!< Construtor taking a single value and making all component equal to that value
{
	data[0] = allValues;
	data[1] = allValues;
}


Vector2D::Vector2D(float x, float y) //!< Constructor taking x,y, and z values
{
	data[0] = x;
	data[1] = y;
}

Vector2D Vector2D::getUnitVector() //!< Returns the unit vector of this vector
{
	float mag = magnitude();
	return Vector2D(data[0] / mag, data[1] / mag);
}


float Vector2D::getX() const //!< Returns the X component of this vector 
{
	return data[0];
}


float Vector2D::getY() const //!< Returns the Y component of this vector
{
	return data[1];
}

float Vector2D::magnitude() //!< Returns the magnitude of this vector
{
	return sqrt(data[0] * data[0] + data[1] * data[1]);
}

Vector2D Vector2D::subtract (const Vector2D& other) //!< Component wise subtraction
{
	return Vector2D(data[0] - other.data[0], data[1] - other.data[1]);
}


Vector2D Vector2D::add (const Vector2D& other) //!< Component wise addition
{
	return Vector2D(data[0] + other.data[0], data[1] + other.data[1]);
}


Vector2D Vector2D::multiply(const Vector2D& other) //!< Component wise multiplication
{
	return Vector2D(data[0] * other.data[0], data[1] * other.data[1]);
}


Vector2D Vector2D::multiply(const float scalar) //!< Component wise scalar multiplication
{
	return Vector2D(data[0] * scalar, data[1] * scalar);
}


float Vector2D::dotProduct(Vector2D& other) //!< Returns the dot product of this vector with other
{
	return data[0] * other.data[0] + data[1] * other.data[1];
}

void Vector2D::set(float x, float y) //!< Set new values in the vector
{
	data[0] = x;
	data[1] = y;
}