#ifndef SPLIT_BELLMAN_SOFT_H
#define SPLIT_BELLMAN_SOFT_H

#include "Split.h"

// Simple Bellman algorithm
// For the CVRP with soft capacity constraints
class Split_Bellman_Soft: public Split 
{

private:

	// Potential vector
	vector < double > potential ; 

	// Index of the predecessor in an optimal path
	vector < int > pred ; 

public:

	Split_Bellman_Soft(Pb_Data * myData) : Split(myData) {}

	int solve();
};

#endif

