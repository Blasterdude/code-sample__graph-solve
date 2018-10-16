/*
 * LHSmap.cpp
 *
 *  Created on: Jan 29, 2017
 *      Author: Thomas J. Meehan
 */

#include "LHSmap.h"

LHSmap::LHSmap() :
		lMap(map<string, LHS>()) {
}

//add entry to map
void LHSmap::add(string str, LHS item) {
	pair<string, LHS> tPair = pair<string, LHS>(str, item);
	lMap.insert(tPair);
}

//return iterator to key
map<string, LHS>::iterator LHSmap::find(string str) {
	return lMap.find(str);
}

map<string, LHS>::iterator LHSmap::end() {
	return lMap.end();
}
map<string, LHS>::iterator LHSmap::begin() {
	return lMap.begin();
}

//return reference to value tied to key
LHS& LHSmap::get(string str) {
	return lMap[str];
}

LHS& LHSmap::operator[](const string& k) {
	return lMap[k];

}

int LHSmap::size() const {
	return lMap.size();
}

/*
 Iterates through the right side of each equation, mapping dependencies and
 adding values together, adding appropriate entries to LHSmap objects to for
 later use by graphing functions to determine best order to fully solve all variables
 */
void LHSmap::solveEquation(string input, string assign) {
	unsigned int sum = 0;
	unsigned int temp = 0;
	vector<string> neededVars;
	string rem = input;

	int beg = 0;
	int last = 0;

	string curVal;

	//optimize for single value equations
	if (input.length() == 1 && !isalpha(input[0])) {
		sum = stoi(input);
	} else {

		//parse to find first each variable and integer value
		while (last != string::npos) {

			rem = rem.substr(last);

			beg = rem.find_first_not_of("+ ");

			last = rem.find_first_of("+ ", beg);

			curVal = rem.substr(beg, last - beg);

			//check if symbol is variable or number
			if (isalpha(curVal[0])) {
				map<string, LHS>::iterator it = find(curVal);

				//add to list of needed variables
				neededVars.push_back(curVal);

				//check if variable already exists in map
				if (it == end()) {
					//if not, create and add partially formed entry to map
					vector<string> vec;
					vec.push_back(assign);
					LHS tVar = LHS(curVal, 0, false, vector<string>(), vec);
					add(curVal, tVar);

				} else {
					//otherwise just add entry to usedBy list
					get(curVal).addUsed(assign);
				}
			} else { //just a number, add to total
				temp = stoi(curVal);
				sum += temp;
			}
		}
	}

	int size = neededVars.size();
	bool solved = (size == 0) ? true : false;

	pair<string, LHS> tPair;
	map<string, LHS>::iterator it = find(assign);

	//check if the LHS being evaluated is already in map
	if (it == end()) {
		//if not create and add
		LHS tVar = LHS(assign, sum, solved, neededVars, vector<string>());
		add(assign, tVar);

	} else {
		//otherwise simply update existing entry
		get(assign).updateVals(sum, solved, neededVars);
	}
}

//sepereates left and right sides of equations for use in solveEquation function
void LHSmap::parseInput(string input) {
	string var;
	int pos = input.find_first_of(" ");
	var = input.substr(0, pos);
	pos = input.find_first_not_of(" =", pos);
	string eq = input.substr(pos);

	solveEquation(eq, var);
}

/*
 Calculate final values for each variable using map lookup

 Assumes topologically sorted order, where all needed variables have
 determined numeric value, resulting in fastest possible solve time
 with minimum backtrack and recursion
 */
void LHSmap::calc(string arg) {
	//if do not already have final numeric value calculate it
	if (!get(arg).getSolved()) {
		int sum = get(arg).getValue();
		//add numeric value for each relevant variable to get final value
		for (const string& s : get(arg).getNeed()) {
			sum += get(s).getValue();
		}
		//update with new values
		get(arg).setValue(sum);
		get(arg).setSolved(true);

	} //nothing to do if already have final value
}

//print final results
void LHSmap::results() const {
	cout << "Final results are:" << endl;
	for (const pair<string, LHS>& x : lMap) {
		cout << x.first << " = " << x.second.getValue() << endl;
	}
}

//reset "visited" status for potential construction of new tree
void LHSmap::resetVisited() {
	for (pair<string, LHS> x : lMap) {
		//cout << x.first << " = " << x.second.getValue() << endl;
		x.second.setVisited(false);
	}

}
