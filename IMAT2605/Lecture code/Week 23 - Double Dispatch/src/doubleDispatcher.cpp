#include "doubleDispatcher.h"

// Function object implementation

string SubClassASubClassAFunction::operator()(BaseClass *a, BaseClass *b)
{
	SubClassA * newA = dynamic_cast<SubClassA*>(a);
	SubClassA * newB = dynamic_cast<SubClassA*>(b);

	return newA->merge(newB);
}

string SubClassASubClassBFunction::operator()(BaseClass *a, BaseClass *b)
{
	SubClassA * newA = dynamic_cast<SubClassA*>(a);
	SubClassB * newB = dynamic_cast<SubClassB*>(b);

	return newA->merge(newB);
}

string SubClassBSubClassAFunction::operator()(BaseClass *a, BaseClass *b)
{
	SubClassB * newA = dynamic_cast<SubClassB*>(a);
	SubClassA * newB = dynamic_cast<SubClassA*>(b);

	return newA->merge(newB);
}

string SubClassBSubClassBFunction::operator()(BaseClass *a, BaseClass *b)
{
	SubClassB * newA = dynamic_cast<SubClassB*>(a);
	SubClassB * newB = dynamic_cast<SubClassB*>(b);

	return newA->merge(newB);
}

// Dispatcher implementation
DoubleDispatcher::DoubleDispatcher()
{
	// Populate the dispatch table
	dispatchTable["class SubClassA"]["class SubClassA"] = new SubClassASubClassAFunction;
	dispatchTable["class SubClassA"]["class SubClassB"] = new SubClassASubClassBFunction;
	dispatchTable["class SubClassB"]["class SubClassA"] = new SubClassBSubClassAFunction;
	dispatchTable["class SubClassB"]["class SubClassB"] = new SubClassBSubClassBFunction;
}

string DoubleDispatcher::dispatch(BaseClass *a, BaseClass *b)
{
	// Identify object RTTI
	string type1 = typeid(*a).name();
	string type2 = typeid(*b).name();

	// Dispatch
	return dispatchTable[type1][type2]->operator()(a,b);
}