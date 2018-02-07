#ifndef SUBCLASSA_H
#define SUBCLASSA_H

#include <string>

#include "baseClass.h"
#include "visitor.h"

using namespace std;

class SubClassA : public BaseClass
{
protected :
	string sSubAString;
public :
	SubClassA(string sNewString);
	void setString(string sNewString);
	string getString();
	void accept(Visitor v);
};

#endif