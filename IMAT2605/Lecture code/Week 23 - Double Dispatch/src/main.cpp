#include <array>
#include <vector>
#include <iostream>

#include "baseClass.h"
#include "subClassA.h"
#include "subClassB.h"

#include "dispatchAlgorithm.h" // For dispatch algorithm

#include "doubleDispatcher.h" // For dispatch table

using namespace std;

int main()
{
	SubClassA instanceOfA1;
	SubClassA instanceOfA2;

	SubClassB instanceOfB1;
	SubClassB instanceOfB2;

	instanceOfA1.setString("Hello");
	instanceOfA2.setString("Goodbye");

	instanceOfB1.setInt(42);
	instanceOfB2.setInt(-18);

	vector<BaseClass *> subClasses;

	subClasses.push_back(&instanceOfA1); 
	subClasses.push_back(&instanceOfA2); 
	subClasses.push_back(&instanceOfB1); 
	subClasses.push_back(&instanceOfB2); 

	// Polymorphic call
	cout << "Double dispatch solved using polymorphism" << endl << endl;
	cout << subClasses.at(0)->merge(subClasses.at(1)) << endl;
	cout << subClasses.at(0)->merge(subClasses.at(2)) << endl;
	cout << subClasses.at(0)->merge(subClasses.at(3)) << endl;
	cout << subClasses.at(1)->merge(subClasses.at(2)) << endl;
	cout << subClasses.at(1)->merge(subClasses.at(3)) << endl;
	cout << subClasses.at(2)->merge(subClasses.at(3)) << endl;

	cout << endl << endl;

	// Dispatch algorithm using RTTI (Run-Time Type Information)
	cout << "Double dispatch solved using dispatch algorithm with RTTI" << endl << endl;
	dispatchAlgorithm da;
	cout << da.dispatch(subClasses.at(0),subClasses.at(1)) << endl;
	cout << da.dispatch(subClasses.at(0),subClasses.at(2)) << endl;
	cout << da.dispatch(subClasses.at(0),subClasses.at(3)) << endl;
	cout << da.dispatch(subClasses.at(1),subClasses.at(2)) << endl;
	cout << da.dispatch(subClasses.at(1),subClasses.at(3)) << endl;
	cout << da.dispatch(subClasses.at(2),subClasses.at(3)) << endl;

	cout << endl << endl;

	// Dispatch Table using RTTI (Run-Time Type Information) with the dispatcher object
	cout << "Double dispatch solved using dispatch table with RTTI" << endl << endl;
	DoubleDispatcher dd;
	cout << dd.dispatch(subClasses.at(0),subClasses.at(1)) << endl;
	cout << dd.dispatch(subClasses.at(0),subClasses.at(2)) << endl;
	cout << dd.dispatch(subClasses.at(0),subClasses.at(3)) << endl;
	cout << dd.dispatch(subClasses.at(1),subClasses.at(2)) << endl;
	cout << dd.dispatch(subClasses.at(1),subClasses.at(3)) << endl;
	cout << dd.dispatch(subClasses.at(2),subClasses.at(3)) << endl;

	cout << endl << endl;

	system("pause");
	return 0;
}