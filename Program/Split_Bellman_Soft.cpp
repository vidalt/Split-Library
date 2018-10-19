
//--------------------------------------------------------
//LIBRARY OF SPLIT ALGORITHM FOR VEHICLE ROUTING PROBLEMS
//Author : Thibaut VIDAL
//Date   : August 15th, 2015. 
//E-mail : vidalt@inf.puc-rio.br
//
//This code is distributed for research purposes.
//All rights reserved.
//--------------------------------------------------------

#include "Split_Bellman_Soft.h"

// The Split algorithm can be viewed as a shortest path in a graph with n+1 nodes
// any edge between nodes i and j corresponds to the trip that goes from the depot 0, i+1, ..., j, 0
int Split_Bellman_Soft::solve()
{ 
	double load, distance, cost ;

	// Initialization of the structures
	potential = vector <double> (myData->nbNodes+1) ; 
	pred =  vector < int > (myData->nbNodes+1) ; 

	for (int i=0 ; i < myData->nbNodes+1 ; i++)
	{
		potential[i] = 1.e30 ; 
		pred[i] = -1 ;
	}
	potential[0] = 0 ;

	for (int i = 0 ; i < myData->nbNodes ; i++)
	{
		load = 0 ;
		distance = 0 ;
		// Optionally, one can impose a hard limit for the total load in the route, e.g., 4Q.
		// This enables to avoid propagating to all successurs, hence reducing the CPU time.
		for (int j = i+1 ; j <= myData->nbNodes /* && load <= 4.0 * myData->vehCapacity */ ; j++)
		{
			load += myData->cli[j].demand ;
			if (j == i+1)
				distance += myData->cli[j].dreturn ;
			else
				distance += myData->cli[j-1].dnext ;
			cost = distance + myData->cli[j].dreturn + myData->penaltyLoad * max<double>(load - myData->vehCapacity, 0);
			if (potential[i] + cost < potential[j] /* && load <= 4.0 * myData->vehCapacity */)
			{
				potential[j] = potential[i] + cost ;
				pred[j] = i ;
			}
		}
	}

	// THE CORE OF THE SPLIT ALGORITHM IS FINISHED HERE, 
	// NOW JUST SWEEPING THE ROUTE in O(n) TO REPORT THE SOLUTION (IN THE GOOD DIRECTION)

	if (potential[myData->nbNodes] > 1.e29)
	{
		cout << "ERROR : no Split solution has been propagated until the last node" << endl ;
		throw string ("ERROR : no Split solution has been propagated until the last node");
	}

	// Finally counting the number of routes using the pred structure (linear complexity) 
	myData->solutionNbRoutes = 0 ;
	int cour = myData->nbNodes ;
	while (cour != 0)
	{
		cour = pred[cour] ;
		myData->solutionNbRoutes ++ ;
	}

	// And filling myData->solution in the good order (linear complexity) 
	cour = myData->nbNodes ;
	for (int i = myData->solutionNbRoutes-1 ; i >= 0 ; i --)
	{
		cour = pred[cour] ;
		myData->solution[i] = cour+1 ;
	}

	myData->solutionCost = potential[myData->nbNodes] ;
	
	return 0 ;
}


