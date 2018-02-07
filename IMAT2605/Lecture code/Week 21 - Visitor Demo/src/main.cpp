#include <iostream>
#include <string>
#include <vector>

#include "subClassA.h"
#include "subClassB.h"
#include "Visitor.h"

int main()
{
	Visitor v;
	vector<BaseClass *> polymorpicContainer;
	polymorpicContainer.push_back(new SubClassA("ABC"));
	polymorpicContainer.push_back(new SubClassB(123));

	for(auto subclass : polymorpicContainer)
	{
		subclass->accept(v);
	}

	system("pause");

	return 0;
}