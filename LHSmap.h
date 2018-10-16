/*
 * LHSmap.h
 *
 *  Created on: Jan 29, 2017
 *      Author: Thomas J. Meehan
 */

#ifndef LHSMAP_H_
#define LHSMAP_H_

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

using namespace std;

/*
 * Class to reperesent a map with strings as keys and LHS objects as the
 * associated values, therefore a simple and fast way to look up a variable's value
 * and other relevant data by using its name
 *
 * Contains most of the logic dealing with parsing the input and calculating values
 */
class LHSmap {
	map<string, LHS> lMap;

public:

	//constructor
	LHSmap();

	//add entry to map
	void add(string str, LHS item);

	/*
	 Traverses through the right side of each equation, mapping dependencies and
	 adding values together, adding appropriate entries to LHSmap objects to for
	 later use by graphing functions to determine best order to fully solve all variables
	 */
	void solveEquation(string input, string assign);

	//return iterator to value associated with key
	map<string, LHS>::iterator find(string str);

	map<string, LHS>::iterator end();
	map<string, LHS>::iterator begin();

	//return reference to value tied to key
	LHS& get(string str);

	//sepereates left and right sides of equations for solveEquation function
	void parseInput(string input);

	/*
	 Calculate final values for each variable

	 Assumes all variables are called in topologically sorted order, where
	 all needed variables have determined numeric value, resulting in fastest
	 possible solve time with no backtrack or recursion
	 */
	void calc(string arg);

	LHS& operator[](const string& k);

	//print final results
	void results() const;

	int size() const;

	//reset "visited" status for potential construction of new tree
	void resetVisited();

};

#endif /* LHSMAP_H_ */
