#include <iostream>

#include "vector2D.h"

using namespace std;

void main()
{
	Vector2D a(0,0);
	cout << "Magnitude is " << a.magnitude() << endl;
	Vector2D b = a.getUnitVector();
}