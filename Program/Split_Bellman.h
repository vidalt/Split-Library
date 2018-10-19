#ifndef SPLIT_BELLMAN_H
#define SPLIT_BELLMAN_H

#include "Split.h"

// Simple Bellman algorithm
// For the CVRP with hard capacity constraints
class Split_Bellman: public Split 
{

private:

	// Potential vector
	vector < double > potential ; 

	// Indice of the predecessor in an optimal path
	vector < int > pred ; 

public:

	Split_Bellman(Pb_Data * myData) : Split(myData) {}

	int solve();
};

#endif

