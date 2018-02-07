#ifndef SUBCLASSB_H
#define SUBCLASSB_H

#include <string>

#include "baseClass.h"
#include "subClassA.h"

using namespace std;

class SubClassB : public BaseClass
{
protected :
	int subBInt;
public :
	void setInt(int iNewInt);
	int getInt();
	string merge(SubClassB * other);
	string merge(SubClassA * other);
	string merge(BaseClass * other); // Added for polymorphic solution
};

#endif