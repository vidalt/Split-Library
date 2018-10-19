#ifndef SPLIT_LINEAR_BOUNDED_H
#define SPLIT_LINEAR_BOUNDED_H

#include "Split.h"

// Simple linear version of Split
// For the CVRP with hard capacity constraints
// and with a limit on the number of available vehicles
class Split_Linear_Bounded: public Split 
{

private:

// Potential vector
vector < vector < double > > potential ;

// Indice of the predecessor in an optimal path
vector < vector < int > > pred ;

// sumDistance[i] for i > 1 contains the sum of distances : sum_{k=1}^{i-1} d_{k,k+1}
vector <double> sumDistance ;

// sumLoad[i] for i >= 1 contains the sum of loads : sum_{k=1}^{i} q_k
vector <double> sumLoad ;

// To be called with i < j only
// Computes the cost of propagating the label i until j
inline double propagate(int i, int j, int k) 
{
	return potential[k][i] + sumDistance[j] - sumDistance[i+1] + myData->cli[i+1].dreturn + myData->cli[j].dreturn ;
}

// Tests if i dominates j as a predecessor for all nodes x >= j+1
// We assume that i < j
inline bool dominates(int i, int j, int k) 
{
	return (sumLoad[i] == sumLoad[j] && potential[k][j] + myData->cli[j+1].dreturn > potential[k][i] + myData->cli[i+1].dreturn + sumDistance[j+1] - sumDistance[i+1] - 0.0001);
}

// Tests if j dominates i as a predecessor for all nodes x >= j+1
// We assume that i < j
inline bool dominatesRight(int i, int j, int k) 
{
	return potential[k][j] + myData->cli[j+1].dreturn < potential[k][i] + myData->cli[i+1].dreturn + sumDistance[j+1] - sumDistance[i+1] + 0.0001 ;
}

public:

	Split_Linear_Bounded(Pb_Data * myData) : Split(myData) {}

	int solve();
};

#endif

