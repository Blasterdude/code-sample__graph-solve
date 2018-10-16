/*
 * LHS.h
 *
 *  Created on: Jan 29, 2017
 *      Author: Thomas J. Meehan
 */

#ifndef LHS_H_
#define LHS_H_

#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <map>
#include <stack>

using namespace std;

/*
 * Class to represent variables found on the "left hand side" of a given equation
 * and their associated data, including numeric values and dependencies on other values
 */

class LHS {
	//name of variable
	string name;
	//numerical value (may be partially solved due to depence on variables)
	unsigned int value;
	//whether variable is completely solved
	bool solved;
	//list of variables whose values are needed to solve the equation
	//(i.e. the variables this object depends on)
	vector<string> needed;
	//list of variables that use the current object
	//(i.e. the variables that depend on this object)
	vector<string> usedBy;
	//whether variable has been visited (for use in dependency graphing)
	bool visited;

public:

	//constructor
	LHS(string n, int v, bool b, vector<string> need, vector<string> used);

	//default constructor
	LHS();

	//add new elements to respective vectors
	void addNeed(string s);
	void addUsed(string s);

	//various getters and setters
	vector<string> getNeed() const;
	vector<string> getUsed() const;
	void updateVals(int val, bool sol, vector<string> pen);
	bool getVisited() const;
	void setVisited(bool v);
	bool getSolved() const;
	void setSolved(bool b);
	int getValue() const;
	void setValue(int given);

};

#endif /* LHS_H_ */
