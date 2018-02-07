#ifndef STACKNODE_H
#define STACKNODE_H

/*! \class StackNode
    \brief A node on a stack data structure using standard pointers
*/

#include <string>

using namespace std;

class StackNode
{
private :
	string data; //!< The element held in the node
	StackNode * next; //!< Next element in the stack
public :
	StackNode(string newData, StackNode * newNext); //!< Constructor
	string getData(); //!< Get the data from the node
	StackNode * getNext(); //!< Get the next data
};

#endif