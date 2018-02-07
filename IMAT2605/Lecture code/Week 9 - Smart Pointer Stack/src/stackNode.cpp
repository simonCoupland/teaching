#include "stackNode.h"

StackNode::StackNode(string newData, shared_ptr<StackNode>& newNext) //!< Constructor
{
	data = newData;
	next = newNext;
}

string StackNode::getData() //!< Get the data from the node
{
	return data;
}


shared_ptr<StackNode> StackNode::getNext() //!< Get the next data
{
	return next;
}
