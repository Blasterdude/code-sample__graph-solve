/*
 * LHS.cpp
 *
 *  Created on: Jan 29, 2017
 *      Author: Thomas J. Meehan
 */

#include "LHS.h"

//constructor
LHS::LHS(string n, int v, bool b, vector<string> need, vector<string> used) :
		name(n), value(v), solved(b), needed(need), usedBy(used), visited(false) {

}

//default constructor
LHS::LHS() :
		name("DEFAULT_NAME"), value(0), solved(false), needed(vector<string>()), usedBy(
				vector<string>()), visited(false) {

}
//add new elements to respective vectors

void LHS::addNeed(string s) {
	needed.push_back(s);
}
void LHS::addUsed(string s) {
	usedBy.push_back(s);
}

//various getters and setters
vector<string> LHS::getNeed() const {
	return needed;
}
vector<string> LHS::getUsed() const {
	return usedBy;
}
void LHS::updateVals(int val, bool sol, vector<string> pen) {
	value = val;
	solved = sol;
	needed = pen;
}
bool LHS::getVisited() const {
	return visited;
}
void LHS::setVisited(bool v) {
	visited = v;
}
bool LHS::getSolved() const {
	return solved;
}
void LHS::setSolved(bool b) {
	solved = b;
}
int LHS::getValue() const {
	return value;
}
void LHS::setValue(int given) {
	value = given;
}

