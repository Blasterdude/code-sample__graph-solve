/*
 * LHSgraph.h
 *
 *  Created on: Jan 29, 2017
 *      Author: Thomas J. Meehan
 *
 *      Based partially on the code examples found at
 *      http://www.geeksforgeeks.org/topological-sorting/
 *
 */

#ifndef LHSGRAPH_H_
#define LHSGRAPH_H_

#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <map>
#include <stack>

#include "LHS.h"
#include "LHSmap.h"

using namespace std;

// A graph class to generate topological sorting of a Directed Acyclic Graph
// used here to generate optimal order to solve each variable
class LHSgraph {

	//Reference to the LHSmap to be sorted
	LHSmap& source;

	//stack variable to store final order
	stack<string> order;

	//Recursive helper used by topologicalSort
	void topologicalSortUtil(string str);

public:

	LHSgraph(LHSmap& obj);   // Constructor

	/*
	 Initiates a topological sort using a modified form of depth first search
	 Generates optimum order to solve equations for variables so that all
	 numeric values for dependent variables are known during calculation
	 */
	void topologicalSort();

	//prints stack results and calls function to determine final value for each variable in topological order
	void calcResults();

};

#endif /* LHSGRAPH_H_ */
