#ifndef SPLIT_BELLMAN_BOUNDED_H
#define SPLIT_BELLMAN_BOUNDED_H

#include "Split.h"

// Simple Bellman algorithm
// For the CVRP with hard capacity constraints
// and with the number of available vehicles limited by 'nbVehicles'
class Split_Bellman_Bounded: public Split 
{

private:

	// Potential vector
	vector < vector <double> > potential ;

	// Indice of the predecessor in an optimal path
	vector < vector <int> > pred ;

public:

	Split_Bellman_Bounded(Pb_Data * myData) : Split(myData) {}

	int solve();
};

#endif

