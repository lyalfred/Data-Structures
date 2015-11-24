// IN Node2.h:
// DOUBLY Linked List Node Class
// Created by Frank M. Carrano and Tim Henry.
// Modified by LyAlfred

#ifndef _NODE
#define _NODE

template<class ItemType>
class Node
{
private:
	ItemType        item;
	Node<ItemType>* next;
	Node<ItemType>* prev;

public:
	Node()							{ next = 0; prev = 0; }
	Node(const ItemType& anItem)		{ item = anItem; next = 0; prev = 0; }
	void setItem(const ItemType& anItem)		{ item = anItem; }
	void setNext(Node<ItemType>* nextNodePtr)	{ next = nextNodePtr; }
	void setPrev(Node<ItemType>* prevNodePtr)	{ prev = prevNodePtr; }
	ItemType getItem() const					{ return item; }
	Node<ItemType>* getNext() const				{ return next; }
	Node<ItemType>* getPrev() const				{ return prev; }
};

#endif
