
//--------------------------------------------------------
//LIBRARY OF SPLIT ALGORITHM FOR VEHICLE ROUTING PROBLEMS
//Author : Thibaut VIDAL
//Date   : August 15th, 2015. 
//E-mail : vidalt@inf.puc-rio.br
//
//This code is distributed for research purposes.
//All rights reserved.
//--------------------------------------------------------

#include "Split_Linear.h"

int Split_Linear::solve()
{ 
	// Initialization of the data structures
	potential = vector <double> (myData->nbNodes+1) ; 
	pred =  vector < int > (myData->nbNodes+1) ; 
	sumDistance = vector <double> (myData->nbNodes+1) ;
	sumLoad = vector <double> (myData->nbNodes+1) ;
	potential[0] = 0 ;
	pred[0] = -1 ; // normally this will never be accessed
	sumDistance[0] = 0 ; // normally this will never be accessed
	sumLoad[0] = 0 ;  // normally this will never be accessed

	for (int i=1 ; i <= myData->nbNodes ; i++)
	{
		potential[i] = 1.e30 ; 
		pred[i] = -1 ;
		sumLoad[i] = sumLoad[i-1] + myData->cli[i].demand ;
		sumDistance[i] = sumDistance[i-1] + myData->cli[i-1].dnext ;
	}

	// Creating the queue
	// Only contains the node "0" in first position.
	Trivial_Deque queue = Trivial_Deque(myData->nbNodes+1,0);

	// Main loop of the program
	for (int i = 1 ; i <= myData->nbNodes ; i++)
	{
		// The front is the best predecessor for i
		potential[i] =  propagate(queue.get_front(),i) ;
		pred[i] = queue.get_front();

		if (i < myData->nbNodes)
		{
			// If i is not dominated by the last of the pile
			if(!dominates(queue.get_back(),i))
			{
				// then i will be inserted, need to remove whoever is dominated by i.
				while (queue.size() > 0 && dominatesRight(queue.get_back(),i))
					queue.pop_back();
				queue.push_back(i);
			}
			// Check if the front is still able to reach the next node, otherwise he will disappear.
			while (sumLoad[i+1] - sumLoad[queue.get_front()] > myData->vehCapacity + 0.0001)
				queue.pop_front();
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