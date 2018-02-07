#ifndef SUBCLASSA_H
#define SUBCLASSA_H

#include <string>

#include "baseClass.h"
#include "subClassB.h"

using namespace std;

class SubClassA : public BaseClass
{
protected :
	string subAString;
public :
	void setString(string sNewString);
	string getString();
	string merge(SubClassA * other);
	string merge(SubClassB * other);
	string merge(BaseClass * other); // Added for polymorphic solution
};

#endif