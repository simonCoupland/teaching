#include "subClassA.h"
#include "subClassB.h"

SubClassA::SubClassA(string sNewString)
{
	sSubAString = sNewString;
}

void SubClassA::setString(string sNewString)
{
	sSubAString = sNewString;
}

string SubClassA::getString()
{
	return sSubAString;
}

void SubClassA::accept(Visitor v)
{
	v.visit(this);
}
