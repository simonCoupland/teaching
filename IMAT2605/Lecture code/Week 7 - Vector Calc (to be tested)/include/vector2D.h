/**
@file vector2D.h
*/

#ifndef VECTOR2D_H
#define VECTOR2D_H

/*! \class Vector2D
\brief A mathematical Vector
*/

#include <cmath>
#include <cstdlib>

class Vector2D
{
protected:
	float data[2]; //!< Data held by the vector data[0] is x and data [1] is y
public:
	Vector2D();  //!< Default consturct, set everything to zero
	Vector2D(float allValues /*!< Value which x and y will be set to */); //!< Construtor taking a single value and making all component equal to that value
	Vector2D(float x /*!< Initial x value */, float y /*!< Initial y value */); //!< Constructor taking x and y values
	float dotProduct(Vector2D& other /*!< other vector for calculation */); //!< Returns the dot product of this vector with other
	Vector2D getUnitVector(); //!< Returns the unit vector of this vector
	float getX() const; //!< Returns the X component of this vector 
	float getY() const; //!< Returns the Y component of this vector
	float magnitude(); //!< Returns the magnitude of this vector
	Vector2D subtract (const Vector2D& other /*!< other vector for calculation */); //!< Component wise subtraction
	Vector2D add (const Vector2D& other /*!< other vector for calculation */); //!< Component wise addition
	Vector2D multiply (const Vector2D& other /*!< other vector for calculation */); //!< Component wise multiplication
	Vector2D multiply (const float scalar /*!< Scalar for calculation */); //!< Component wise scalar multiplication
	void set(float x /*!< New x value */, float y /*!< New y value */); //!< Set new values in the vector
};

#endif