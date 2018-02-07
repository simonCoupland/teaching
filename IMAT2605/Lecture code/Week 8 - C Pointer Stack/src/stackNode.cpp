#include "stackNode.h"

StackNode::StackNode(string newData, StackNode * newNext) //!< Constructor
{
	data = newData;
	next = newNext;
}

string StackNode::getData() //!< Get the data from the node
{
	return data;
}

StackNode * StackNode::getNext() //!< Get the next data
{
	return next;
}