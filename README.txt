Coding Challenge
Submitted by Thomas J. Meehan
tmeehan@wpi.edu
1/29/17

The included source code represents my solution to a coding challenge: A command-line program to evaluate a set of equations defined in a given text file, where each equation defines a variable in terms of addition of positive integers and other variables.

Compiling:
To compile, simply use the included makefile by invoking “make” inside the directory. All files are compiled with G++ and the c++11 -std=c++11 flag. Standard libraries are utilized but no external libraries should be necessary to compile. If any issues arise refer to the makefile.

Usage:
When compiled it generates an executable called “solve”, which can be used as follows:

./solve <input_file_name>

Where <input_file_name> is simply text file containing series of equations, with one equation defined per line. An equation is defined as <LHS> = <RHS> where the left side is always a variable name and the right side can be composed of variables, unsigned integers, and the + operator.
Here is one example set of equations:offset = 4 + random + 1location = 1 + origin + offsetorigin = 3 + 5random = 2

Examples:
Example input and output can be found in the EXAMPLES.txt file.

Insights:
This was a very interesting problem with many different potential ways to go about solving it. Some of the more interesting choices made include using a map instead of an unordered map to associate variable names with the LHS class structure. This decision was made in order to ensure that the map stored all data automatically in an alphabetically sorted order based on variable name to facilitate simple alphabetical data output at the end, at the slight cost of lookup speed. Depending on real world applications and how often certain operations are performed (alphabetical output versus search/insert/deletion and how robust the hash function is at avoiding collisions) either structure may be preferred.  Interestingly, a “trie” based map may be the absolute best way to handle such a task, but constructing one seemed outside the scope of this coding challenge. Another interesting choice was to use topographical sort and dependency lists in order to facilitate the most efficient order of calculating values, ultimately leading to a reduced time complexity. 

Time Complexity:
Overall the time complexity of this solution is approximately O(V * T + V * E + V * e) with V = the number of variables (lines in input file), T = number of tokens per line (ints and variables) and E = the number of edges in the graph (total number of variable dependencies) and e = the number of decencies per variable. 

My submission consists of 7 total source files:

main.cpp: The main driver program that reads input from the desired file and calls the necessary class functions to generate a solution.

LHS.cpp and LHS.h: Contains a class to represent a variable and its values / dependencies on other variables for a solution.

LHSmap.cpp and LHSmap.h: Contains a class to represent a mapping of strings (names of variables) and LHS objects to facilitate simple and quick way to look up a variable’s value and other data based on its name. As a result it also contains most of the logic dealing with parsing the input and calculating values.

LHSgraph.cpp and LHSgraph.h: Contains a graph class to generate topological sorting of a Directed Acyclic Graph, used in this case to generate optimal order to solve each variable.



All code contained within is entirely my own work with the exception of some of the graph functions found in LHSgraph.cpp/h, which was based on the code examples found at http://www.geeksforgeeks.org/topological-sorting/


Original Problem Statement:
Your task is to write a command-line program to evaluate a set ofequations, each specified on separate lines. An equation is definedby:
<LHS> = <RHS>
<LHS> is the left-hand side of the equation and is always a variablename. A variable name can only be composed of letters from thealphabet (e.g. for which isalpha(c) is 1). <RHS> is the right handside of the equation and can be composed of variables, unsignedintegers, and the + operator.
Here is one example set of equations:offset = 4 + random + 1location = 1 + origin + offsetorigin = 3 + 5random = 2
Your program should take a filename as input. The file contains a setof equations, like the above. It should evaluate the set of equationsand print the unsigned integer value of each variable.
<variable name> = <unsigned integer value>
The output should be sorted by in ascending order by variable name.
The output for the example above would be:location = 16offset = 7origin = 8random = 2
You may assume the following: You may assume the input is well formed.There will be one or more white spaces between each token. You may useC++, the Standard C libraries and the Standard Template Library (STL).You may use std::sort and qsort. All variables in the equation setwill have a definition. You may also assume a variable is only definedonce and will have a valid integer solution.

