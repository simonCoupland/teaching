#include "dispatchAlgorithm.h"

// Private methods for dispatching different pairs of subclass types
string dispatchAlgorithm::SubClassASubClassA(SubClassA a, SubClassA b)
{
	return a.merge(&b);
}

string dispatchAlgorithm::SubClassBSubClassB(SubClassB a, SubClassB b)
{
	return a.merge(&b);
}

string dispatchAlgorithm::SubClassBSubClassA(SubClassB a, SubClassA b)
{
	return a.merge(&b);
}

string dispatchAlgorithm::SubClassASubClassB(SubClassA a, SubClassB b)
{
	return a.merge(&b);
}

string dispatchAlgorithm::dispatch(BaseClass *a, BaseClass *b)
{
	string typeA = typeid(*a).name();
	string typeB = typeid(*b).name();

	if(typeA == "class SubClassA" && typeB == "class SubClassA") 
	{
		SubClassA newA = *(dynamic_cast<SubClassA*>(a));
		SubClassA newB = *(dynamic_cast<SubClassA*>(b));
		return SubClassASubClassA(newA, newB);
	}

	if(typeA == "class SubClassB" && typeB == "class SubClassB") 
	{
		SubClassB newA = *(dynamic_cast<SubClassB*>(a));
		SubClassB newB = *(dynamic_cast<SubClassB*>(b));
		return SubClassBSubClassB(newA, newB);
	}

	if(typeA == "class SubClassA" && typeB == "class SubClassB") 
	{
		SubClassA newA = *(dynamic_cast<SubClassA*>(a));
		SubClassB newB = *(dynamic_cast<SubClassB*>(b));
		return SubClassASubClassB(newA, newB);
	}

	if(typeA == "class SubClassB" && typeB == "class SubClassA") 
	{
		SubClassB newA = *(dynamic_cast<SubClassB*>(a));
		SubClassA newB = *(dynamic_cast<SubClassA*>(b));
		return SubClassBSubClassA(newA, newB);
	}
}

