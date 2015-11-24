//*********************************************************************
// IN THE HashSC file:
#pragma once
#include "List.h"
#include <cmath>
#include "HashTable.h"
using namespace std;

// ---------------------- HashSC Prototype --------------------------
template <class Object>
class HashSC: public HashTable<Object> // FIX HERE TO BE A DERIVED CLASS OF HashTable
{
	static const int INIT_TABLE_SIZE = 43; // USE THIS INIT. SIZE FOR HW#5
	static const float INIT_MAX_LAMBDA;
private:
	List<Object> * mLists; // for array of linked lists
	int mSize;  // number of entries
	int mTableSize; // array size
	float mMaxLambda; // max. load factor
public:
	HashSC(int(*hashFcn)(const Object &obj), int(*comp)(const Object&left, const Object&right), int tableSize = INIT_TABLE_SIZE); // FIX HERE: need add'l parameters
	~HashSC();
	bool contains(const Object & x) const;
	void makeEmpty();
	bool insert(const Object & x);
	bool remove(const Object & x);
	static long nextPrime(long n);
	int size() const { return mSize; }
	bool setMaxLambda(float lm);
	bool getEntry(const Object & target, Object & returnedItem) const; // ADDED FOR HW#5
	void displayStatistics() const; // ADDED FOR HW#5
	void traverseTable(void visit(Object &item)); // ADDED FOR HW#5

private:
	void rehash();
	int myHash(const Object & x) const;
	void(*visit) (Object &item);	// visit function
	int(*compare) (const Object &left, const Object &right);
};

template <class Object>
const float HashSC<Object>::INIT_MAX_LAMBDA = 1.5;


// HashSC method definitions -------------------
template <class Object>// FIX BELOW: add'l parameters, call base constructor
HashSC<Object>::HashSC(int(*hashFcn)(const Object &obj), int(*comp)(const Object&left, const Object&right), int tableSize) : 
	HashTable(hashFcn, comp) , mSize(0)
{
	if (tableSize < INIT_TABLE_SIZE)
		mTableSize = INIT_TABLE_SIZE;
	else
		mTableSize = nextPrime(tableSize);

	mLists = new List<Object>[mTableSize];
	mMaxLambda = INIT_MAX_LAMBDA;
	compare = comp;

}
	
template <class Object>
HashSC<Object>::~HashSC()
{
	delete[] mLists;
}

template <class Object>
void HashSC<Object>::displayStatistics() const
{
	cout << "\nIn the HashSC class:\n";
	cout << "Table Size = " << dec << mTableSize << endl;
	cout << "Number of entries = " << mSize << endl;
	cout << "Load factor = " << (double)mSize / mTableSize << endl;
	cout << "Number of collisions = " << dec << this->collisionCount << endl;
	cout << "Longest Linked List = " << this->longestCollisionRun << endl << endl;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// DON'T FORGET TO OVERRIDE traverseTable() (YOU WRITE FOR HW#5)
//     See assignment for what to include 
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
template <class Object>
void HashSC<Object>::traverseTable(void visit(Object &item))
{
	Object tempObj;
	for (int i = 0; i < mTableSize; i++)		
	{
		int a = 1;
		while (mLists[i].getEntry(a, tempObj))
		{
			visit(tempObj);
			a++;
		}
	}
}

template <class Object>
int HashSC<Object>::myHash(const Object & x) const
{
	int hashVal;

	hashVal = this->Hash(x) % mTableSize; //may need to do: this->Hash(x)
	if (hashVal < 0)
		hashVal += mTableSize;

	return hashVal;
}

template <class Object>
void HashSC<Object>::makeEmpty()
{
	int k;

	for (k = 0; k < mTableSize; k++)
		mLists[k].clear();
	mSize = 0;
}

template <class Object>
bool HashSC<Object>::contains(const Object & x) const
{
	const List<Object> & theList = mLists[myHash(x)];
	Object tempObj;
	for (int i = 0; i < theList.size(); i++)
	{
		theList.getEntry((i + 1), tempObj);
//		if (tempObj == x)		// CHANGE TO USE this->compare function         return true;
		if (compare(tempObj, x) == 0)
			return true;
	}

	// not found
	return false;
}

template <class Object>
bool HashSC<Object>::getEntry(const Object & target, Object & returnedItem) const
{
	// FINISH THIS (should be like remove, but assign to returnedItem if found)
	List<Object> &theList = mLists[myHash(target)];
	Object tempObj;
	for (int i = 0; i < theList.size(); i++)
	{
		theList.getEntry((i + 1), tempObj);
//		if (tempObj == target)
		if (compare(tempObj, target) == 0)
		{
			returnedItem = tempObj;
			return true;
		}
	}
	//not found
	return false;
}

template <class Object>
bool HashSC<Object>::remove(const Object & x)
{
	List<Object> &theList = mLists[myHash(x)];
	Object tempObj;

	for (int i = 0; i < theList.size(); i++)
	{
		theList.getEntry((i + 1), tempObj);
//		if (tempObj == x)		// CHANGE TO USE this->compare function
		if (compare(tempObj, x) == 0)
		{
			theList.remove(i + 1);
			mSize--;
			return true;
		}
	}
	// not found
	return false;
}

template <class Object>
bool HashSC<Object>::insert(const Object & x)
{
	List<Object> &theList = mLists[myHash(x)];
	int listSize = theList.size();
	Object tempObj;

	for (int i = 0; i < listSize; i++)
	{
		theList.getEntry((i + 1), tempObj);
//		if (tempObj == x) {		// CHANGE TO USE this->compare function
		if (compare(tempObj, x) == 0)
			return false;
	}

	// ADD HERE: check and maybe increment member counter variable
	if (theList.insert(x))
		mSize++;
	// not found so we insert at the beginning
//	theList.insert(x);

	//increment collisionCount
	if (!theList.isEmpty())
		collisionCount += theList.size();
	// ADD HERE: possibly update longestCollisionRun variable
	if (longestCollisionRun < theList.size())
		longestCollisionRun = theList.size();
	//    which should be counting the longest linked list
	// check load factor
	if (++mSize > mMaxLambda * mTableSize)
	{				// ADD CODE HERE TO RESET THE HashTable COUNTERS TO 0
		collisionCount = 0;
		longestCollisionRun = 0;
		rehash();
	}

	return true;
}

template <class Object>
void HashSC<Object>::rehash()
{
	List<Object> *oldLists = mLists;
	int k, oldTableSize = mTableSize;
	List<Object> *currList;
	Object tempObj;

	mTableSize = nextPrime(2 * oldTableSize);
	mLists = new List<Object>[mTableSize];

	mSize = 0;
	for (k = 0; k < oldTableSize; k++)
	{
		currList = &oldLists[k];
		for (int i = 0; i < currList->size(); ++i)
		{
			currList->getEntry((i + 1), tempObj);
			insert(tempObj);
		}

	}
	delete[] oldLists;
}

template <class Object>
bool HashSC<Object>::setMaxLambda(float lam)
{
	if (lam < .1 || lam > 100)
		return false;
	mMaxLambda = lam;
	return true;
}

template <class Object>
long HashSC<Object>::nextPrime(long n)
{
	long k, candidate, loopLim;

	// loop doesn't work for 2 or 3
	if (n <= 2)
		return 2;
	else if (n == 3)
		return 3;

	for (candidate = (n % 2 == 0) ? n + 1 : n; true; candidate += 2)
	{
		// all primes > 3 are of the form 6k +/- 1
		loopLim = (long)((sqrt((float)candidate) + 1) / 6);

		// we know it is odd.  check for divisibility by 3
		if (candidate % 3 == 0)
			continue;

		// now we can check for divisibility of 6k +/- 1 up to sqrt
		for (k = 1; k <= loopLim; k++)
		{
			if (candidate % (6 * k - 1) == 0)
				break;
			if (candidate % (6 * k + 1) == 0)
				break;
		}
		if (k > loopLim)
			return candidate;
	}
}

// END OF HashSC class
