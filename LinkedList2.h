#ifndef LINKEDLIST2_H_INCLUDED
#define LINKEDLIST2_H_INCLUDED

// Doubly Linked List abstract base class
// By LyAlfred

#include "Node2.h"

template<class ItemType>
class LinkedList2
{
protected:
	Node<ItemType>* headPtr; // Pointer to (dummy) first node in the list
	Node<ItemType>* tailPtr; // Pointer to (dummy) last node in the list
	int itemCount;           // Current count of list items

public:
	// constructor
	LinkedList2();
	// copy constructor
	LinkedList2(const LinkedList2<ItemType>& aList);
	// destructor
	virtual ~LinkedList2()	{ clear(); }

	// check for empty list
	bool isEmpty() const	{ return itemCount == 0; }
	// get number of entries in the list
	int size() const		{ return itemCount; }
	// remove all entries from list
	void clear();
	// display list from front to end
	void display() const;
	// display list from end to front
	void displayBackwards() const;
	// abstract insert function
	virtual bool insert(const ItemType& newEntry, int newPosition = 1) = 0;
};

template<class ItemType>
LinkedList2<ItemType>::LinkedList2()
{
	itemCount = 0;
	headPtr = new Node<ItemType>();
	tailPtr = new Node<ItemType>(); // fixed
	headPtr->setNext(tailPtr);
	tailPtr->setPrev(headPtr);
}

template<class ItemType>
LinkedList2<ItemType>::LinkedList2(const LinkedList2<ItemType>& aList)
{
	itemCount = aList.itemCount;
	Node<ItemType>  *origChainPtr;

	origChainPtr = aList.headPtr;

	headPtr = new Node<ItemType>();		// copy dummy head node

	// Copy remaining nodes BEFORE tailPtr
	Node<ItemType>* newChainPtr = headPtr; // ignore data
	origChainPtr = origChainPtr->getNext();
	while (origChainPtr != aList.tailPtr)
	{
		ItemType nextItem = origChainPtr->getItem();
		Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
		newChainPtr->setNext(newNodePtr); // link prev to current
		newNodePtr->setPrev(newChainPtr); // link current to prev

		newChainPtr = newChainPtr->getNext();
		origChainPtr = origChainPtr->getNext();
	}
	// Create tail and init. prev
	tailPtr = new Node<ItemType>();
	tailPtr->setPrev(newChainPtr);
	newChainPtr->setNext(tailPtr);
}

template<class ItemType>
void LinkedList2<ItemType>::display() const
{
	Node<ItemType>* currPtr = headPtr->getNext();//****FOR 4.2
	while (currPtr != tailPtr)			//****FOR LAB EX. 4.2
	{
		cout << currPtr->getItem() << " ";	// display data
		currPtr = currPtr->getNext();		// go to next node
	}
	cout << endl << endl;
}

template<class ItemType>
void LinkedList2<ItemType>::displayBackwards() const
{
	// YOU COMPLETE THIS SO IT DISPLAYS EACH ITEM STARTING FROM BEFORE THE TAIL
	//    TO THE NODE AFTER THE HEAD (DON'T DISPLAY THE TAIL OR HEAD ITEMS)!
	Node<ItemType>* temp = tailPtr->getPrev();

	while (temp != headPtr)
	{
		cout << temp->getItem() << endl;
		temp = temp->getPrev();
	}
}

template<class ItemType>
void LinkedList2<ItemType>::clear()
{
	Node<ItemType> * deletePtr, *nodePtr;

	deletePtr = headPtr->getNext(); //****FOR LAB EX. 4.2
	for (int i = 0; i < itemCount; i++) // walk each node
	{
		nodePtr = deletePtr->getNext();//****FOR LAB EX. 4.2
		delete deletePtr;
		deletePtr = nodePtr;    //****FOR LAB EX. 4.2
	}
	// UPDATE the headPtr and tailPtr here:
	headPtr->setNext(tailPtr); // *****FOR LAB EX. 4.2
	tailPtr->setPrev(headPtr); // *****FOR LAB EX. 4.2

	itemCount = 0;
}


#endif // LINKEDLIST2_H_INCLUDED
