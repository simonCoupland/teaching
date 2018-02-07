#include "subClassB.h"{


void SubClassB::setInt(int iNewInt)
{
	subBInt = iNewInt;
}

int SubClassB::getInt()
{
	return subBInt;
}

string SubClassB::merge(SubClassB * other)
{
	return to_string(subBInt) + " - " + to_string(other->subBInt);
}

string SubClassB::merge(SubClassA * other)
{
	return to_string(subBInt) + " - " + other->getString();
}

string SubClassB::merge(BaseClass * other) // Added for polymorphic solution
{
	return other->merge(this);
}
