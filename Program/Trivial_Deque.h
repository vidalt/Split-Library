#ifndef TRIVIAL_DEQUE_H
#define TRIVIAL_DEQUE_H

#include "Pb_Data.h"

// Simple Deque which is used for all Linear Split algorithms
class Trivial_Deque
{

private:

	// Simply a vector structure to keep the elements of the queue
	vector <int> myDeque ;

	// Index of the front element
	int indexFront ;

	// Index of the back element
	int indexBack ;

public:

	// Removes the front element of the queue D
	inline void pop_front () 
	{
		indexFront ++ ;
	}

	// Removes the back element of the queue D
	inline void pop_back () 
	{
		indexBack -- ;
	}

	// Appends a new element to the back of the queue D
	inline void push_back (int i) 
	{
		indexBack ++ ;
		myDeque[indexBack] = i ;
	} 

	// make sure that the queue has at least 1 elements before calling this function, 
	// I will not do the test inside this function for matters of performance
	inline int get_front () 
	{
		return myDeque[indexFront] ;
	}

	// make sure that the queue has at least 2 elements before calling this function
	inline int get_next_front () 
	{
		return myDeque[indexFront+1] ;
	}

	// make sure that the queue has at least 1 elements before calling this function
	inline int get_back () 
	{
		return myDeque[indexBack] ;
	}

	// returns the current number of elements in the queue
	inline int size ()
	{
		return indexBack - indexFront + 1 ;
	}

	// resets the queue to its initial state with only one element (still the same size)
	// but avoids to change the memory allocation (faster than deleting and reconstructing a new object)
	void reset (int firstNode)
	{
		myDeque[0] = firstNode ;
		indexBack = 0 ;
		indexFront = 0 ;
	}

	Trivial_Deque(int nbElements, int firstNode) 
	{
		myDeque = vector <int> (nbElements) ;
		myDeque[0] = firstNode ;
		indexBack = 0 ;
		indexFront = 0 ;
	}

	~Trivial_Deque() {}
};

#endif

