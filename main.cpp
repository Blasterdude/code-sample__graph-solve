//============================================================================
// Name        : tesla.cpp
// Author      : Thomas J. Meehan
// Version     : 1.2.5
// Copyright   :
// Description : Tesla's coding challenge:
//				 A command-line program to evaluate a set of equations defined
//				 in a given text file, where each equation defines a variable
//				 in terms of addition of positive integers and other variables
//============================================================================

#include "LHS.h"
#include "LHSmap.h"
#include "LHSgraph.h"

int main(int argc, char * argv[]) {

	string line;
	//check to make sure argument for text file is given
	if (argc != 2) {
		cout
				<< "USAGE: Must provide single command line argument indicating file to be used for input"
				<< endl;
	}
	ifstream myfile(argv[1]);

	LHSmap vMap = LHSmap();
	//read in text file line by line
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			//go through each line to calculate values and find dependencies
			vMap.parseInput(line);
		}
		myfile.close();

		// Create a graph of the variable dependencies
		LHSgraph g(vMap);

		//determine optimal order to solve each variable
		g.topologicalSort();

		//use that order to determine value for each variable
		g.calcResults();

		//print results
		vMap.results();

	} else { //if there was an error opening file
		cout << "Unable to open file" << endl;
	}
	return 0;
}

