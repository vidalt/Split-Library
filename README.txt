
--------------------------------------------------------
LIBRARY OF SPLIT ALGORITHM FOR VEHICLE ROUTING PROBLEMS
Author : Thibaut VIDAL
Date   : August 15th, 2015. 
E-mail : vidalt@inf.puc-rio.br
Website: http://w1.cirrelt.ca/~vidalt/en/VRP-resources.html

This code is distributed for research purposes.
All rights reserved.
--------------------------------------------------------

This package provides 6 simple version of the Split algorithm, described in:
"Vidal, Thibaut (2016). Technical note: Split algorithm in O(n) for the capacitated vehicle routing problem.
Computers & Operations Research. 69, 40–47. DOI: https://doi.org/10.1016/j.cor.2015.11.012".
The author accepted manuscript is also available at https://arxiv.org/pdf/1508.02759.pdf.
In particular, an implementation of a Split algorithm in O(n) is included.

Below are the computational complexities of the algorithms, for a problem with n delivery points and
a maximum of B deliveries per route (as a consequence of the capacity constraints):

Split_Bellman          |  Bellman algorithm                                          | O(nB)
Split_Bellman_Bounded  |  Bellman algorithm with a limit m on the number of routes   | O(n²m)
Split_Bellman_Soft     |  Bellman algorithm with soft capacity constraints           | O(n²)
---------------------------------------------------------------------------------------------
Split_Linear           |  Linear algorithm                                           | O(n)
Split_Linear_Bounded   |  Linear algorithm  with a limit m on the number of routes   | O(nm)
Split_Linear_Soft      |  Linear algorithm  with soft capacity constraints           | O(n)


-------------------------------------------------------------------------------------------------------
INSTALLATION:

To run the code, simply unzip the archive, and use the command "make" in the same folder as the program.
The program can then be executed with the following command: 

./split INSTANCE_PATH
By default, the Split_Linear solver is used.

Several other arguments are available to run different versions of the solver:

./split INSTANCE_PATH -solver SOLVER_TYPE 
can be used to test a different solver, the solver types are :
SOLVER_TYPE in {SPLIT_BELLMAN, SPLIT_BELLMAN_BOUNDED, SPLIT_BELLMAN_SOFT,  SPLIT_LINEAR, SPLIT_LINEAR_BOUNDED, SPLIT_LINEAR_SOFT}
Note that the bounded and soft solvers require additional data as input 
(number of vehicles or penalty for a unit excess of capacity)

./split INSTANCE_PATH -solver SPLIT_LINEAR_BOUNDED -veh X
Will run the linear split with a fleet size limit of X vehicles

./split INSTANCE_PATH -solver SPLIT_LINEAR_SOFT -pen Y
Will run the linear split with soft capaciity constraints and a penalty of Y per unit of capacity excess.


-------------------------------------------------------------------------------------------------------
BENCHMARK INSTANCES:

Benchmark instances are also provided with the code, in the folder "Instances/".
All details on the generation of these instances are provided in the associated paper.
-------------------------------------------------------------------------------------------------------





