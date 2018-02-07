#ifndef VISITOR_H
#define VISITOR_H

#include <iostream>

#include "SubClassA.h"
#include "SubClassB.h"

using namespace std;

class Visitor
{
public:
	void visit(SubClassA * pa);
	void visit(SubClassB * pb);
};

#endif