#include "subClassA.h"

void SubClassA::setString(string sNewString)
{
	subAString = sNewString;
}

string SubClassA::getString()
{
	return subAString;
}

string SubClassA::merge(SubClassA * other)
{
	return subAString + " - " + other->getString();
}

string SubClassA::merge(SubClassB * other)
{
	return subAString + " - " + to_string(other->getInt());
}

string SubClassA::merge(BaseClass * other) // Added for polymorphic solution
{
	return other->merge(this);
}

