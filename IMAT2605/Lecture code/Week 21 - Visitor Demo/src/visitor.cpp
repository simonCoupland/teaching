#include "visitor.h"

void Visitor::visit(SubClassA * pa)
{
	cout << "SubClassA: " << pa->getString() << endl;
}

void Visitor::visit(SubClassB * pb)
{
	cout << "SubClassB: " << pb->getInt() << endl;
}
