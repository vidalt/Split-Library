
//--------------------------------------------------------
//LIBRARY OF SPLIT ALGORITHM FOR VEHICLE ROUTING PROBLEMS
//Author : Thibaut VIDAL
//Date   : August 15th, 2015. 
//E-mail : vidalt@inf.puc-rio.br
//
//This code is distributed for research purposes.
//All rights reserved.
//--------------------------------------------------------

#include "commandline.h"
#include "Split_Bellman.h"
#include "Split_Bellman_Soft.h"
#include "Split_Bellman_Bounded.h"
#include "Split_Linear.h"
#include "Split_Linear_Soft.h"
#include "Split_Linear_Bounded.h"
#include <iostream>

int main (int argc, char *argv[])
{
	Pb_Data * myData ;
	Split * mySolver ;

	commandline c(argc, argv);
	if (c.is_valid())
	{
		// Parsing the problem instance
		myData = new Pb_Data(c.get_path_to_instance(),c.get_solver_type(),c.get_nbVeh(),c.get_penaltyLoad());

		// Begin of clock
		myData->time_StartComput = clock();

		// Create the solver data structures
		if (myData->solverType      == BELLMAN)
			mySolver = new Split_Bellman(myData);
		else if (myData->solverType == BELLMAN_SOFT)
			mySolver = new Split_Bellman_Soft(myData);
		else if (myData->solverType == BELLMAN_BOUNDED)
			mySolver = new Split_Bellman_Bounded(myData);
		else if (myData->solverType == LINEAR)
			mySolver = new Split_Linear(myData);
		else if (myData->solverType == LINEAR_SOFT)
			mySolver = new Split_Linear_Soft(myData);
		else if (myData->solverType == LINEAR_BOUNDED)
			mySolver = new Split_Linear_Bounded(myData);
		else
		{
			cout << "ERROR : no solver with this name" << endl ;
			throw string ("ERROR : no solver with this name") ;
		}
		
		// Compute here the split solution
		mySolver->solve() ;

		// End of clock
		myData->time_EndComput = clock() ;

		// Check and Print the solution
		myData->printSolution() ;
		myData->checkSolution() ;

		// the time measure is not precise on a single instance
		// to make more precise time measures, the code inside this function needs to be looped several times.
		// cout << "CPU Time (Only Split) : " << myData->time_EndComput - myData->time_StartComput << endl ;

		delete myData ;
	}
	else
		throw string("ERROR : Non-valid commandline, Usage : myProgram instance [-sol solution] [-solver solverType]");
}
