#include "stack.h"	

Stack::Stack() //!< Default constructor
{
	top = nullptr; // No data so top is null
	size = 0; // Stack is empty to begin with
}

void Stack::push(string newElement) //!< Push on to the stack
{
	top = new StackNode(newElement, top); // Add the new element
	size++; // Add one to the stack size
}

string Stack::pop() //!< Pop an item off the stack
{
	string result = top->getData(); // Get the data to return
	top = top->getNext(); // Set the top item to be the next item in the stack
	size--; // Decrease the stack size
	return result; // Return the data which was at the top of the stack
}

bool Stack::empty() //! Returns whether or not the stack is empty
{
	return size == 0;
}