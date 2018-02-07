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
	float m_data[2]; //!< Data held by the vector
public:
	Vector2D();  //!< Default consturct, set everything to zero
	Vector2D(float allValues /*!< Value which x and y will be set to */); //!< Construtor taking a single value and making all component equal to that value
	Vector2D(float x /*!< Initial x value */, float y /*!< Initial y value */); //!< Constructor taking x and y values
	void set(float x, float y); //!< Set new values in the vector
	float x() const; //!< Returns the X component of this vector 
	float y() const; //!< Returns the Y component of this vector
	float angle(Vector2D& other /*!< other vector for calculation */) const; //!< angle between this vector and other
	float dotProduct(Vector2D& other /*!< other vector for calculation */) const; //!< Returns the dot product of this vector with other
	float crossProduct(Vector2D& other /*!< other vector for calculation */) const; //!< Returns the cross product of this vector with other
	Vector2D crossProduct(float scalar /* Some scalar quantity */) const;  //!< Returns the cross product of this vector with scalar
	Vector2D unitVector() const; //!< Returns the unit vector of this vector
	float magnitude() const; //!< Returns the magnitude of this vector
	Vector2D operator- (const Vector2D& other /*!< other vector for calculation */) const; //!< Component wise subtraction
	Vector2D operator+ (const Vector2D& other /*!< other vector for calculation */) const; //!< Component wise addition
	Vector2D operator* (const Vector2D& other /*!< other vector for calculation */) const; //!< Component wise multiplication
	Vector2D operator* (const float scalar /*!< Scalar for calculation */) const; //!< Component wise scalar multiplication
	
};

#endif