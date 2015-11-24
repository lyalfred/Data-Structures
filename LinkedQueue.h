#ifndef _LINKED_QUEUE
#define _LINKED_QUEUE

#include "QueueInterface.h"
#include "Node.h"

template<class ItemType>
class LinkedQueue : public QueueInterface<ItemType>
{
private:
	Node<ItemType>* backPtr;
	Node<ItemType>* frontPtr;
	int count;

public:
	LinkedQueue() { backPtr = NULL, frontPtr = NULL, count = 0; }
	LinkedQueue(const LinkedQueue& aQueue);
	~LinkedQueue();
	int size() const { return count; }
	bool isEmpty() const { return (count == 0); }
	bool enqueue(const ItemType& newEntry);
	bool dequeue();
	ItemType peekFront() const { return frontPtr->getItem(); }
};


template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue& aQueue)
{	
	Node<ItemType>* origChainPtr = aQueue.frontPtr;  // original chain is linked list to be copied

	count = aQueue.count;
	if (origChainPtr == 0)
		frontPtr = 0;
	else
	{
		frontPtr = new Node<ItemType>();				// copy top item
		frontPtr->setItem(origChainPtr->getItem());

		Node<ItemType>* newChainPtr = topPtr;			// new chain starts at top
		origChainPtr = origChainPtr->getNext();		// start with next item in original chain

		while (origChainPtr != 0)						// copy rest of list
		{
			ItemType nextItem = origChainPtr->getItem();
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);	// create new node
			newChainPtr->setNext(newNodePtr);							// add new node to list
			newChainPtr = newChainPtr->getNext();						// walk to next item
			origChainPtr = origChainPtr->getNext();
		}
		newChainPtr->setNext(0);						// set end of list
	}
}


template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
	Node<ItemType> *next;
	// write code for this
	while (frontPtr != NULL)
	{
		next = frontPtr->getNext();
		delete frontPtr;
		frontPtr = next;
	}
}


template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry)
{
	// code to add data
	Node<ItemType> *temp = new Node<ItemType>(newEntry); 
	//temp->item = newEntry;
	//temp->next = NULL;
	if (isEmpty())
	{
		frontPtr = temp;
	}
	else
	{
		backPtr->setNext(temp);
	}
	backPtr = temp;
	//delete temp;
	count++;
	return true;
}


template<class ItemType>
bool LinkedQueue<ItemType>::dequeue()
{
	Node<ItemType> *temp = new Node<ItemType>();
	if (frontPtr == NULL)
		return false;
	else
	{
		temp = frontPtr;
		frontPtr = frontPtr->getNext();
		delete temp;
	}
	// code to remove data
	count--;
	return true;
}

#endif
