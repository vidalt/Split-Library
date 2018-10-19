#include "commandline.h"

void commandline::set_instance_name(string to_parse)
{ instance_name = to_parse; }

int commandline::set_solver_type(string to_parse)
{ 
	if (to_parse == "BELLMAN")
		solverType = BELLMAN ;
	else if (to_parse == "BELLMAN_SOFT")
		solverType = BELLMAN_SOFT ;
	else if (to_parse == "BELLMAN_BOUNDED")
		solverType = BELLMAN_BOUNDED ;
	else if (to_parse == "LINEAR")
		solverType = LINEAR ;
	else if (to_parse == "LINEAR_SOFT")
		solverType = LINEAR_SOFT ;
	else if (to_parse == "LINEAR_BOUNDED")
		solverType = LINEAR_BOUNDED ;
	else
		return -1; // problem

	return 0 ; // OK
}

void commandline::display_problem_name(string to_parse)
{ 
    char caractere1 = '/' ;
    char caractere2 = '\\' ;

    int position = (int)to_parse.find_last_of(caractere1) ;
	int position2 = (int)to_parse.find_last_of(caractere2) ;
	if (position2 > position) position = position2 ;

	if (position != -1)
		cout << "INSTANCE     : " << to_parse.substr(position+1,to_parse.length() - 1)  << endl ;
	else
		cout << "INSTANCE     : " << to_parse << endl ;
}

// constructeur
commandline::commandline(int argc, char* argv[])
{
	bool isOutput = false ;
	bool isNameSpecified = false ;
	
	if (argc%2 != 0 || argc > 8 || argc < 2)
	{
		cout << "ERROR : invalid command line" << endl ;
		cout << "USAGE : ./executable path_to_instance [-solver solver_type] [-veh nb_vehicles] [-pen penalty_factor]" << endl ;
		throw string ("ERROR : invalid command line") ;
        command_ok = false;
	}
	else
	{
		// Default values
		set_instance_name(string(argv[1]));
		display_problem_name(string(argv[1]));
		nbVeh = -1 ;
		penaltyLoad = 1.e30 ;

		// parameters
		for ( int i = 2 ; i < argc ; i += 2 )
		{
			if ( string(argv[i]) == "-solver" )
			{
				if (set_solver_type(string(argv[i+1])) != 0)
					throw string ("ERROR : Unrecognized solver type : " + string(argv[i+1])) ;
				cout << "ALGORITHM    : " << argv[i+1] << endl ;
				isNameSpecified = true ;
			}
			else if ( string(argv[i]) == "-veh" )
			{
				nbVeh = atoi(argv[i+1]);
				cout << "NB VEHICLES  : " << nbVeh << endl ;
			}
			else if ( string(argv[i]) == "-pen" )
			{
				penaltyLoad = atof(argv[i+1]);
				cout << "PENALTY LOAD : " << penaltyLoad << endl ;
			}
			else
			{
				throw string ("ERROR : Unrecognized command : " + string(argv[i])) ;
				command_ok = false ;
			}
		}

		if (!isNameSpecified)
		{
			solverType = LINEAR ;
			cout << "ALGORITHM    : LINEAR " << endl ;
		}

		if (nbVeh == -1 && (solverType == BELLMAN_BOUNDED || solverType == LINEAR_BOUNDED)) 
		{
			cout << "ERROR : For solvers with limited fleet, need to specify a fleet size by using '-veh XXX' in the commandline" << endl ;
			throw string ("ERROR : For solvers with limited fleet, need to specify a fleet size by using '-veh XXX' in the commandline") ;
		}

		if (penaltyLoad == 1.e30 && (solverType == BELLMAN_SOFT || solverType == LINEAR_SOFT)) 
		{
			cout << "ERROR : For solvers with soft capacity constraints, need to specify the penalty factor using '-pen XXX' in the commandline" << endl ;
			throw string ("ERROR : For solvers with soft capacity constraints, need to specify the penalty factor using '-pen XXX' in the commandline") ;
		}

		command_ok = true;
	}
}

commandline::~commandline(){}

string commandline::get_path_to_instance()
{
    return instance_name;
}

SolverType commandline::get_solver_type()
{
	return solverType ;
}

int commandline::get_nbVeh()
{
	return nbVeh ;
}

double commandline::get_penaltyLoad()
{
	return penaltyLoad ;
}

bool commandline::is_valid()
{
    return command_ok;
}
