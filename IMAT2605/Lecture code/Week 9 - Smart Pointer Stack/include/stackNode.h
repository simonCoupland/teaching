#ifndef STACKNODE_H
#define STACKNODE_H

/*! \class StackNode
    \brief A node on a stack data structure using smart pointers
*/

#include <string>
#include <memory>

using namespace std;

class StackNode
{
private :
	string data; //!< The element held in the node
	shared_ptr<StackNode> next; //!< Next element in the stack
public :
	StackNode(string newData, shared_ptr<StackNode>& newNext); //!< Constructor
	string getData(); //!< Get the data from the node
	shared_ptr<StackNode> StackNode::getNext(); //!< Get the next pointer
};

#endif