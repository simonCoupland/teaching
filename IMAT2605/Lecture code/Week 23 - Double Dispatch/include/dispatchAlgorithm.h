#ifndef DISPATCHALGORITHM_H
#define DISPATCHALGORITHM_H

#include "baseClass.h"
#include "subClassA.h"
#include "subClassB.h"

class dispatchAlgorithm
{
private:
	string SubClassASubClassA(SubClassA a, SubClassA b);
	string SubClassBSubClassB(SubClassB a, SubClassB b);
	string SubClassBSubClassA(SubClassB a, SubClassA b);
	string SubClassASubClassB(SubClassA a, SubClassB b);
public:
	string dispatch(BaseClass *a, BaseClass *b);
};


#endif