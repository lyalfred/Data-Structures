// Sorted Linked list ADT
// In SortedList2.h

#ifndef _SORTED_LIST
#define _SORTED_LIST

#include "LinkedList2.h"
#include "Node2.h"

template<class ItemType>
class SortedList2 : public LinkedList2<ItemType>
{
private:
	Node<ItemType>* getPreviousNode(const ItemType& anEntry) const;

public:
	// Inserts an entry in the correct sorted order, position is ignored
	bool insert(const ItemType& newEntry, int newPosition = 1);
	// Removes an entry
	bool remove(const ItemType& anEntry);
	// Returns true for found, false for not found anEntry
	bool getEntry(const ItemType & target, ItemType & returnedEntry) const;
};

template<class ItemType>
Node<ItemType>* SortedList2<ItemType>::getPreviousNode(const ItemType& anEntry) const
{
	Node<ItemType>* prev, *curr;
	
	prev = headPtr; //CHANGE THIS STATEMENT prev STARTS AT THE DUMMY HEAD NODE
	curr = headPtr->getNext(); //CHANGE THIS STATEMENT SO YOU SKIP THE DUMMY HEAD NODE
	while (curr != tailPtr && curr->getItem() < anEntry)//CHANGE THIS SO YOU STOP AT THE DUMMY TAIL NODE
	{
//		prev = curr;
		curr = curr->getNext();
	} // end while
	return curr->getPrev(); // must NEVER return 0 EVEN if empty
	

}

template<class ItemType>
bool SortedList2<ItemType>::insert(const ItemType& newEntry, int newPosition)
{
	Node<ItemType> * prevNode, *newNode, *nextNode;
	// IN THE SORTEDLIST, WE'LL IGNORE position
	prevNode = getPreviousNode(newEntry);
	nextNode = prevNode->getNext();
	if (nextNode != tailPtr && nextNode->getItem() == newEntry)
		return false; // don't allow duplicates IN THIS ASSIGNMENT

	newNode = new Node<ItemType>(newEntry);
	prevNode->setNext(newNode);
	nextNode->setPrev(newNode);
	newNode->setNext(nextNode);
	newNode->setPrev(prevNode);
	itemCount++;
	return true;
}

template<class ItemType>
bool SortedList2<ItemType>::remove(const ItemType& anEntry)
{
	bool found = false;
	Node<ItemType> * prevNode, *nodeToDelete, *nextNode;

	// YOU COMPLETE THIS FUNCTION (similar to insert, BUT NOT THE SAME):
	// Required in this function:
	//     call getPreviousNode ONLY ONCE in this function
	//     check if the node after the previous one found equals anEntry
	//     	(return false if it's not equal)
	//     update the pointers in the previous and following nodes
	//        (you figure out which ones, what would make sense here?)
	//     delete the node AND DECREMENT THE itemCount if found
	if(headPtr == 0)						// empty list?
		return found;
	prevNode = getPreviousNode(anEntry);	// try to find node
	nodeToDelete = prevNode->getNext();			// save "found" node
	if (anEntry == nodeToDelete->getItem())	// find the node?
	{
		nextNode = nodeToDelete->getNext(); // get node after
		nextNode->setPrev(prevNode);
		prevNode->setNext(nextNode);		// change prev's next
		if (nodeToDelete == headPtr)		// deleting the head?
		{	
			headPtr = nextNode;				// update headPtr		
		}
		delete nodeToDelete;
		found = true;
		--itemCount;
	}
	return found;
}

template<class ItemType>
bool SortedList2<ItemType>::getEntry(const ItemType & target, ItemType & returnedEntry) const
{
	bool found = false;
	Node<ItemType>* prevNode, *foundNode;
	// YOU COMPLETE THIS FUNCTION (similar to insert, BUT NOT THE SAME):
	// Required in this function:
	//	  DON'T CHANGE ANYTHING in this SortedList2 object
	//     call getPreviousNode ONLY ONCE in this function
	//     assign the found Node's item to returnedEntry (IF found)
	//     assign true to found (IF found)

	
		prevNode = getPreviousNode(target);
		foundNode = prevNode->getNext();
		if (foundNode->getItem() == target)
		{
			returnedEntry = foundNode->getItem();
			found = true;
		}
	return found;
}

#endif 
