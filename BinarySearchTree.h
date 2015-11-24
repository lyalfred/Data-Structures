//IN BinarySearchTree.h:
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "BinaryTree.h"
#include "BinaryNode.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
	//*********** ADD A POINTER TO FUNCTION AS DESCRIBED ON THE ASSIGNMENT********
	int(*compare) (const ItemType & newEntry, const ItemType & anEntry);
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
	

public:
	//*********** ADD A CONSTRUCTOR AS DESCRIBED ON THE ASSIGNMENT********
	BinarySearchTree(int compare1(const ItemType&, const ItemType&))
	{
		compare = compare1;
	}
	//*********** ADD A COPY CONSTRUCTOR AS DESCRIBED ON THE ASSIGNMENT********
	BinarySearchTree(BinarySearchTree<ItemType> const & temp)
	{
		compare = temp.compare;
		this->copyTree(temp.rootPtr);

	}
//	BinarySearchTree()
	// insert a node at the correct location 
	bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
	// NOT IN THE Tree Code Files on Catalyst, use for HW#4:
	BinarySearchTree & operator=(const BinarySearchTree & sourceTree);
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	rootPtr = _insert(rootPtr, newNodePtr);
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	rootPtr = _remove(rootPtr, target, isSuccessful);
	return isSuccessful;
}

//*****************************COMPLETE THIS******************************
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
	// MUST INCLUDE CALLING THE PRIVATE findNode FUNCTION
	// Be sure to check if the findNode function actually finds anEntry
	// If it does, assign to the returnedItem parameter the item of the 
	//     found node and return true
	// If it doesn't, return false

	BinaryNode<ItemType>* foundNode;
	if (findNode(this->rootPtr, anEntry))
	{
		foundNode = findNode(this->rootPtr, anEntry);
		returnedItem = foundNode->getItem();
		return true;
	}
	else
		return false;

}

//NOT IN THE Tree Code Files on Catalyst, use for HW#4:
template<class ItemType>
BinarySearchTree<ItemType> & BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType> & sourceTree)
{
	compare = sourceTree.compare;
	this->BinaryTree::operator=(sourceTree);
	return *this;
}


//////////////////////////// private functions //////////////////////////////////

// Done as class exercise:
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
	BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
		return newNodePtr;
	if (compare(newNodePtr->getItem(), nodePtr->getItem())<0) //newNodePtr->getItem() < nodePtr->getItem()) *****CHANGE THIS*****
		nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
	else
		nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
	return nodePtr; // must return
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
	const ItemType target, bool & success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (compare(nodePtr->getItem(), target) > 0)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (compare(nodePtr->getItem(), target) < 0)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else	// found the node
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
	ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


//*****************************COMPLETE THIS******************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
	const ItemType & target) const
{
	// ALGORITHM:
	//       IF nodePtr doesn't exist (is 0) THEN
	//            return 0
	//       ELSE IF nodePtr's item > target THEN (make sure you use the compare function)
	//                return what the recursive call to findNode, for the leftPtr, returns
	//       ELSE IF nodePtr's item < target THEN (make sure you use the compare function)
	//            return what the recursive call to findNode, for the leftPtr, returns
	//	ELSE
	if (nodePtr == 0)
		return 0;
	else if (compare(nodePtr->getItem(), target)>0)
	{
		return findNode(nodePtr->getLeftPtr(), target);
	}
	else if (compare(nodePtr->getItem(), target) < 0)
	{
		return findNode(nodePtr->getRightPtr(), target);
	}
	else
		return nodePtr;

}

template<class ItemType>
int compare(const ItemType & left, const ItemType & right)
{
	if (left < right) return -1;
	if (right > left) return 1;
	return 0;

}

#endif