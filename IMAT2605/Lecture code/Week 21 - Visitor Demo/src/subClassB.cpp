#include "subClassB.h"

SubClassB::SubClassB(int iNewInt)
{
	iSubBInt = iNewInt;
}

void SubClassB::setInt(int iNewInt)
{
	iSubBInt = iNewInt;
}

int SubClassB::getInt()
{
	return iSubBInt;
}

void SubClassB::accept(Visitor v)
{
	v.visit(this);
}