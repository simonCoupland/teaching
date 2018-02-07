#ifndef BASECLASS_H
#define BASECLASS_H

#include <string>

class SubClassA;
class SubClassB;

#include "visitable.h"

using namespace std;

class BaseClass : Visitable
{
public :
	virtual void accept(Visitor v) = 0;
};



#endif