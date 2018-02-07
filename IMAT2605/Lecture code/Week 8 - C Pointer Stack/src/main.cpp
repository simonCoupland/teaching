/**
@file main.cpp
*/


/*! \mainpage Stack Functionality
 *
 * Implementation of a stack using smart pointers.
 */

#include <iostream>
#include "stack.h"

void main() /** Entry point for the application */
{
	Stack myStack;
	myStack.push("\n");
	myStack.push("Thanks for the memory!");
	myStack.push("\n");
	myStack.push("Stack");
	myStack.push("I am a");
	myStack.push("World");
	myStack.push("Hello");

	while(!myStack.empty())
	{
		std::cout << myStack.pop() << std::endl;
	}
	
	system("pause");
}
