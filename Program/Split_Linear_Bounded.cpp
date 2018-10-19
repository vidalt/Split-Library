
//--------------------------------------------------------
//LIBRARY OF SPLIT ALGORITHM FOR VEHICLE ROUTING PROBLEMS
//Author : Thibaut VIDAL
//Date   : August 15th, 2015. 
//E-mail : vidalt@inf.puc-rio.br
//
//This code is distributed for research purposes.
//All rights reserved.
//--------------------------------------------------------

#include "Split_Linear_Bounded.h"

int Split_Linear_Bounded::solve()
{ 
	// Initialization of the data structures for cost evaluations
	sumDistance = vector <double> (myData->nbNodes+1) ;
	sumLoad = vector <double> (myData->nbNodes+1) ;
	sumDistance[0] = 0 ; // normally this will never be accessed
	sumLoad[0] = 0 ;  // normally this will never be accessed
	for (int i=1 ; i <= myData->nbNodes ; i++)
	{
		sumLoad[i] = sumLoad[i-1] + myData->cli[i].demand ;
		sumDistance[i] = sumDistance[i-1] + myData->cli[i-1].dnext ;
	}

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

	// Creating the queue
	// Only contains the node "0" in first position.
	Trivial_Deque queue = Trivial_Deque(myData->nbNodes+1,0);

	// Main loop of the program
	for (int k = 0 ; k < myData->nbVehicles ; k++)
	{
		// in the Split problem there is always one feasible solution with k routes that reaches the index k in the tour.
		queue.reset(k); 

		// The range of potentials < 1.29 is always an interval.
		// The size of the queue will stay >= 1 until we reach the end of this interval.
		for (int i = k+1 ; i <= myData->nbNodes && queue.size() > 0 ; i++)
		{
			// The front is the best predecessor for i
			potential[k+1][i] = propagate(queue.get_front(), i, k); 
			pred[k+1][i] = queue.get_front();

			// If i is not dominated by the last of the pile 
			if (i < myData->nbNodes)
			{
				if (!dominates(queue.get_back(),i,k))
				{
					// then i will be inserted, need to remove whoever he dominates
					while (queue.size() > 0 && dominatesRight(queue.get_back(),i,k))
						queue.pop_back();
					queue.push_back(i);
				}

				// Check if the front is able to reach the next node, otherwise he will disappear.
				while (queue.size() > 0 && sumLoad[i+1] - sumLoad[queue.get_front()] > myData->vehCapacity + 0.0001)
					queue.pop_front();
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