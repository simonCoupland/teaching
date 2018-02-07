#ifndef STACKNODE_H
#define STACKNODE_H

/*! \class StackNode
    \brief A node on a stack data structure using smart pointers
*/

#include <string>
#include <memory>

using namespace std;

template <class G>
class StackNode
{
private :
	G data; //!< The element held in the node
	shared_ptr<StackNode<G>> next; //!< Next element in the stack
public :
	StackNode(G newData, shared_ptr<StackNode<G>>& newNext); //!< Constructor
	G getData(); //!< Get the data from the node
	shared_ptr<StackNode<G>> StackNode::getNext(); //!< Get the next pointer
};

template <class G>
StackNode<G>::StackNode(G newData, shared_ptr<StackNode>& newNext) //!< Constructor
{
	data = newData;
	next = newNext;
}

template <class G>
G StackNode<G>::getData() //!< Get the data from the node
{
	return data;
}

template <class G>
shared_ptr<StackNode<G>> StackNode<G>::getNext() //!< Get the next data
{
	return next;
}

#endif