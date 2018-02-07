#ifndef DOUBLEDISPATCHER_H
#define DOUBLEDISPATCHER_H

#include "baseClass.h"
#include "subClassA.h"
#include "subClassB.h"

#include <map>

// Function objects for dispatch table

class BaseFunction
{
public:
	virtual string operator()(BaseClass *a, BaseClass *b) = 0;
};

class SubClassASubClassAFunction : public BaseFunction
{
public :
	 string operator()(BaseClass *a, BaseClass *b);
};

class SubClassASubClassBFunction : public BaseFunction
{
public :
	 string operator()(BaseClass *a, BaseClass *b);
};

class SubClassBSubClassAFunction : public BaseFunction
{
public :
	 string operator()(BaseClass *a, BaseClass *b);
};

class SubClassBSubClassBFunction : public BaseFunction
{
public :
	 string operator()(BaseClass *a, BaseClass *b);
};


// Object containing the dispatch table
class DoubleDispatcher
{
private :
	map<string,map<string, BaseFunction*>> dispatchTable; //!< Dispatch table - maps pairs of dispatch types to polymorphic function objects
public:
	DoubleDispatcher(); //!< Default constructor - populate the dispatch table
	string dispatch(BaseClass *a, BaseClass *b); //!< Dispatch a pair of objects (sub classes)
};

#endif