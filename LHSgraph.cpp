/*
 * LHSgraph.cpp
 *
 *  Created on: Jan 29, 2017
 *      Author: thomasjmeehan
 */

#include "LHSgraph.h"

//constructor
LHSgraph::LHSgraph(LHSmap& sor) :
		source(sor) {
}

//Recursive helper used by topologicalSort
void LHSgraph::topologicalSortUtil(string str) {
	//Mark the current node as visited.
	source.get(str).setVisited(true);

	//Recur for all the nodes pointed to by this vertex
	//AKA those that require its value to calculate their own values
	for (string& s : source[str].getUsed()) {
		if (!source[s].getVisited()) {
			topologicalSortUtil(s);
		}
	}

	//Push current vertex to stack to store result and form topological order
	order.push(str);
}

/*
 Initiates a topological sort using a modified form of depth first search
 Generates optimum order to solve equations for variables so that all
 numeric values for dependent variables are known during calculation
 */
void LHSgraph::topologicalSort() {
	// Iterate through each unvisited node
	for (const pair<string, LHS>& x : source) {
		if (x.second.getVisited() == false) {
			topologicalSortUtil(x.first);
		}
	}
}

//Unwinds stack results and calls function to determine final value for each variable in topological order
void LHSgraph::calcResults() {
	//go through stack in order
	while (order.empty() == false) {
		//caculated final value before pop
		source.calc(order.top());
		order.pop();
	}
}
