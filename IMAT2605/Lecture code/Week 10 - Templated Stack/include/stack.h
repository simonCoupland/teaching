#ifndef STACK_H
#define STACK_H

/*! \class Stack
    \brief A stack data structure using smart pointers
*/

#include <string>
#include <memory>

#include "stackNode.h"

using namespace std;

template <class G>
class Stack
{
private :
	unsigned int size; //!< Number of elements in the stack
	shared_ptr<StackNode<G>> top; //!< Item at the top of the stack
public :

	Stack(); //!< Default constructor
	void push(G newElement); //!< Push on to the stack
	G pop(); //!< Pop an item off the stack
	bool empty(); //! Returns whether or not the stack is empty
};

template <class G>
Stack<G>::Stack() //!< Default constructor
{
	top = nullptr; // No data so top is null
	size = 0; // Stack is empty to begin with
}

template <class G>
void Stack<G>::push(G newElement) //!< Push on to the stack
{
	top = shared_ptr<StackNode<G>>(new StackNode<G>(newElement, top)); // Add the new element
	size++; // Add one to the stack size
}

template <class G>
G Stack<G>::pop() //!< Pop an item off the stack
{
	G result = top->getData(); // Get the data to return
	top = top->getNext(); // Set the top item to be the next item in the stack
	size--; // Decrease the stack size
	return result; // Return the data which was at the top of the stack
}

template <class G>
bool Stack<G>::empty() //! Returns whether or not the stack is empty
{
	return size == 0;
}

#endif