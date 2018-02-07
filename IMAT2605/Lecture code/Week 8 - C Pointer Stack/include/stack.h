#ifndef STACK_H
#define STACK_H

/*! \class Stack
    \brief A stack data structure using standrd pointers
*/

#include <string>

#include "stackNode.h"

using namespace std;

class Stack
{
private :
	unsigned int size; //!< Number of elements in the stack
	StackNode * top; //!< Item at the top of the stack
public :

	Stack(); //!< Default constructor
	void push(string newElement); //!< Push on to the stack
	string pop(); //!< Pop an item off the stack
	bool empty(); //! Returns whether or not the stack is empty
};

#endif