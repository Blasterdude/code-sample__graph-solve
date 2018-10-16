all: solve

solve: main.o LHS.o LHSmap.o LHSgraph.o
	g++ -o solve main.o LHS.o LHSmap.o LHSgraph.o

main.o: main.cpp LHS.h LHSmap.h LHSgraph.h
	g++ -c -std=c++11 main.cpp -o main.o

LHS.o: LHS.cpp LHS.h
	g++ -c -std=c++11 LHS.cpp -o LHS.o

LHSmap.o: LHSmap.cpp LHSmap.h LHS.h
	g++ -c -std=c++11 LHSmap.cpp -o LHSmap.o

LHSgraph.o: LHSgraph.cpp LHSgraph.h LHSmap.h LHS.h
	g++ -c -std=c++11 LHSgraph.cpp -o LHSgraph.o

clean:
	rm *.o