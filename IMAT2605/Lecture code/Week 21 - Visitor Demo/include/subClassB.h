#ifndef SUBCLASSB_H
#define SUBCLASSB_H

#include <string>

#include "baseClass.h"
#include "visitor.h"

using namespace std;

class SubClassB : public BaseClass
{
protected :
	int iSubBInt;
public :
	SubClassB(int iNewInt);
	void setInt(int iNewInt);
	int getInt();
	void accept(Visitor v);
};



#endif