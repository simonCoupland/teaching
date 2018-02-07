#ifndef BASECLASS_H
#define BASECLASS_H

#include <string>

using namespace std;

// Forward declarations for the compilers benefit, added for polymorphic solution
class SubClassA;
class SubClassB;

class BaseClass
{
protected :
public :
	virtual string merge(BaseClass * other) = 0; // Added for polymorphic solution
	virtual string merge(SubClassA * other) = 0; // Added for polymorphic solution
	virtual string merge(SubClassB * other) = 0; // Added for polymorphic solution
};



#endif