//IN BinaryTree.h:
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree
	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);
public:
	// "admin" functions
	BinaryTree()					{ rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree){ rootPtr = copyTree(sourceTree.rootPtr); }// see assignment
	virtual ~BinaryTree()				{ clear(); }// CALL clear()		
	BinaryTree & operator=(const BinaryTree & sourceTree);

	// common functions for all binary trees
	bool isEmpty() const				{ return count == 0; }
	int size() const					{ return count; }
	void clear(){ cout << "\nClearing old tree\n\n"; destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void preOrder(void visit(ItemType &)) const		{ _preorder(visit, rootPtr); }
	void inOrder(void visit(ItemType &)) const		{ _inorder(visit, rootPtr); }
	void postOrder(void visit(ItemType &)) const	{ _postorder(visit, rootPtr); }

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0;
	virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;

};

//////////////////////////////////////////////////////////////////////////

//*****************************COMPLETE THIS******************************
template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;
	// FILL IN SEVERAL LINES HERE USING THE ALGORITHM:
	//    If nodePtr doesn't exist (is 0) Then return 0
	//    
	//	Assign a new BinaryNode to newNodePtr
	//	Set the newNodePtr's data (item) to the nodePtr's item
	//	Set the newNodePtr's leftPtr to 
	//		a recursive call to copyTree for the nodePtr's leftPtr
	//  Set the newNodePtr's rightPtr to
	//		a recursive call to copyTree for the nodePtr's rightPtr
	//	INCREMENT count
	if (nodePtr == 0)
		return 0;
	else
	{
		//	newNodePtr->setItem(nodePtr->getItem());
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem());
		newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
		count++;
	}
	return newNodePtr;
}

//*****************************COMPLETE THIS******************************
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	//FILL IN SEVERAL LINES HERE, USING THE ALGORITHM:
	//    if nodePtr doesn't exist (is 0), return
	//    destroy the left subtree (recursive call to destroyTree)
	//    destroy the right subtree (recursive call to destroyTree)
	//    delete nodePtr
	if (nodePtr == 0)
		return;
	else
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
		return;
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

//*****************************COMPLETE THIS******************************
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	// see _preorder for similar code
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

//*****************************COMPLETE THIS******************************
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	// CALL copyTree and return *this
	if (rootPtr != 0) // already filled tree?
		clear(); // clear old tree
	rootPtr = copyTree(sourceTree.rootPtr);
	return *this;
}
#endif