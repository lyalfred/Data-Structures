// Array implementation of Stack ADT
// Created by Frank M. Carrano and Tim Henry
// Modified by Ly Alfred

#ifndef _ARRAY_STACK
#define _ARRAY_STACK

#include "StackInterface.h"

const int MAX_STACK = 5;

template<class ItemType>
class ArrayStack : public StackInterface<ItemType>
{
private:
	ItemType items[MAX_STACK]; // Array of stack items
	int      top;              // Index to top of stack
	int 	 count;			   // Size of the stack

public:
	ArrayStack() { top = -1; count = 0; }
	bool isEmpty() const { return (top == -1); }
	bool push(const ItemType& newEntry);
	bool pop();
	ItemType peek() const { return items[top]; }
	int size() const { return count; }
};

/////////////// add to this class so it's not an abstract class

template<class ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry)
{
	bool result = false;
	if (top < MAX_STACK - 1)
	{
		count++;
		top++;
		items[top] = newEntry;
		result = true;
	}
	return result;
}


template<class ItemType>
bool ArrayStack<ItemType>::pop()
{
	bool result = false;
	if (top != -1)    //////////// make this check more efficient
	{
		count--;
		top--;
		result = true;
	}
	return result;
}


#endif
