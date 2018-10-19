
//--------------------------------------------------------
//LIBRARY OF SPLIT ALGORITHM FOR VEHICLE ROUTING PROBLEMS
//Author : Thibaut VIDAL
//Date   : August 15th, 2015. 
//E-mail : vidalt@inf.puc-rio.br
//
//This code is distributed for research purposes.
//All rights reserved.
//--------------------------------------------------------

#include "Split_Bellman_Bounded.h"

// The Split algorithm can be viewed as a shortest path in a graph with n+1 nodes
// any edge between nodes i and j corresponds to the trip that goes from the depot 0, i+1, ..., j, 0
int Split_Bellman_Bounded::solve()
{ 
	double load, distance, cost ;

	// Initialization of the potential, pred and queue data structures
	vector <double> tempDbl = vector <double> (myData->nbNodes+1) ; 
	vector <int> tempInt =  vector < int > (myData->nbNodes+1) ; 
	for (int i=0 ; i <= myData->nbNodes ; i++)
	{
		tempDbl[i] = 1.e30 ; 
		tempInt[i] = -1 ;
	}

	potential = vector < vector <double> > (myData->nbVehicles+1) ; 
	pred = vector < vector <int> >  (myData->nbVehicles+1) ; 
	for (int k=0 ; k <= myData->nbVehicles ; k++)
	{
		potential[k] = tempDbl ;
		pred[k] = tempInt ;
	}
	potential[0][0] = 0 ;

	// Main part of the Split algorithm
	for (int k = 0 ; k < myData->nbVehicles ; k++)
	{
		for (int i = k ; i < myData->nbNodes ; i++)
		{
			load = 0 ;
			distance = 0 ;
			for (int j = i+1 ; j <= myData->nbNodes && load <= myData->vehCapacity ; j++)
			{
				load += myData->cli[j].demand ;
				if (j == i+1)
					distance += myData->cli[j].dreturn ;
				else
					distance += myData->cli[j-1].dnext ;
				cost = distance + myData->cli[j].dreturn ;
				if (potential[k][i] + cost < potential[k+1][j] && load <= myData->vehCapacity)
				{
					potential[k+1][j] = potential[k][i] + cost ;
					pred[k+1][j] = i ;
				}
			}
		}
	}

	// THE CORE OF THE SPLIT ALGORITHM IS FINISHED HERE, 
	// NOW JUST SWEEPING THE ROUTE in O(n) TO REPORT THE SOLUTION (IN THE GOOD DIRECTION)

	// Each potential[k][myData->nbNodes] for k >= 1 corresponds to a min cost path with exactly k edges.
	// Finding the optimal number of edges first
	// For now we assume that the path should have exactly myData->nbVehicles edges, just need to search in linear time for the case with less edges.
	if (potential[myData->nbVehicles][myData->nbNodes] > 1.e29)
	{
		cout << "ERROR : no Split solution has been propagated until the last node" << endl ;
		throw string ("ERROR : no Split solution has been propagated until the last node");
	}

	// Finding the optimal number of routes
	double minCost = 1.e30 ;
	for (int k=1 ; k <= myData->nbVehicles ; k++)
	{
		if (potential[k][myData->nbNodes] < minCost)
		{
			minCost = potential[k][myData->nbNodes] ;
			myData->solutionNbRoutes = k ;
		}
	}

	// And filling myData->solution in the good order (linear complexity) 
	int cour = myData->nbNodes ;
	for (int i = myData->solutionNbRoutes-1 ; i >= 0 ; i --)
	{
		cour = pred[i+1][cour] ;
		myData->solution[i] = cour+1 ;
	}

	myData->solutionCost = potential[myData->solutionNbRoutes][myData->nbNodes] ;
	return 0 ;
}


