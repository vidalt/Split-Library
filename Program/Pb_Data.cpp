
//--------------------------------------------------------
//LIBRARY OF SPLIT ALGORITHM FOR VEHICLE ROUTING PROBLEMS
//Author : Thibaut VIDAL
//Date   : August 15th, 2015. 
//E-mail : vidalt@inf.puc-rio.br
//
//This code is distributed for research purposes.
//All rights reserved.
//--------------------------------------------------------

#include "Pb_Data.h"

Pb_Data::Pb_Data(string pathToInstance, SolverType solverType, int nbVeh, double penaltyLoad) : pathToInstance(pathToInstance), solverType(solverType), nbVehicles(nbVeh), penaltyLoad(penaltyLoad)
{
	// For now it's hard coded, but should be a variable of the problem or a commandline input
	ifstream fichier ;
	ofstream outFile ;
	string contenu ;
	string uselessStr ;

	// to generate different demands for each instance
	srand((unsigned int)time(NULL)); 

	/* parsing the TSPlib instance and deriving node and depot informations */
	fichier.open(pathToInstance.c_str());
	if (fichier.is_open())
	{
		// just skipping useless entries in the header and filling the general problem data
		getline(fichier, contenu);
		getline(fichier, contenu);
		fichier >>  uselessStr ;
		fichier >>  uselessStr ;
		fichier >>  nbNodes ;
		fichier >>  uselessStr ;
		fichier >>  uselessStr ;
		fichier >>  vehCapacity ;
		getline(fichier, contenu);
		getline(fichier, contenu);

		// creating the data structure for clients
		// to match the index of the auxiliary graph, the node 0 in the vector of Clients will be a sentinel (which can somehow stand for the depot)
		cli = vector <Client> (nbNodes+1) ;
		cli[0].demand = 0 ;
		cli[0].dreturn = 0 ;
		cli[0].dnext = 0 ;
		cli[0].index = 0 ;
		for (int i = 1 ; i <= nbNodes ; i++)
		{
			fichier >> cli[i].index ;
			fichier >> cli[i].demand ;
			fichier >> cli[i].dreturn ;
			if (i < nbNodes)
				fichier >> cli[i].dnext ;
			else
				cli[i].dnext = -1 ;
		}

		// little debugging test
		fichier >> uselessStr ;
		if (!(uselessStr == "EOF"))
		{
			cout << "ERROR when reading instance, not finding EOF when it should be" << endl ;
			throw string ("ERROR when reading instance, not finding EOF when it should be");
		}

		// if there are too many vehicles, simply reducing it to a more reasonable value
		if (nbVehicles > nbNodes) 
			nbVehicles = nbNodes ;

		// creating the solution structure
		solution = vector <int> (nbNodes) ;
		for (int i=0 ; i < nbNodes ; i++)
			solution[i] = -1 ;

		fichier.close();
	}
	else 
	{
		cout << "ERROR : Impossible to find instance file : " << pathToInstance << endl ;
		throw string("ERROR : Impossible to find instance file : " + pathToInstance);
	}
}

Pb_Data::~Pb_Data(void)
{}