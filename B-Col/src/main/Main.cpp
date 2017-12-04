/*
 * Main.cpp
 *
 *  Created on: 19 de dez de 2016
 *      Author: marcio
 */


#include "../tools/Graph.h"
#include "../tools/Set.h"
#include "../tools/Timer.h"
#include "../solver/Solver.h"
#include "../solver/Heuristic.h"
#include "../solver/BasicHeuristic.h"
#include "../solver/TrivialHeuristic.h"
#include "../solver/ImpRepresentative.h"
#include "../solver/NewRepresentative.h"
#include "Reader.h"
#include <cstdio>
#include <zlib.h>

int main(int argc, char **argv){

	//input file
	std::ifstream ifs (argv[1], std::ifstream::in);
	//output file
	FILE* fout = fopen(argv[2], "a");

	//the reader for the graph
	Reader myReader;

	//the graph
	Graph * g = myReader.read(ifs);

	//the abstract solver to the problem
	Solver* solver;

	printf("TESTING GRAPH %s \n", argv[1]);

	//an simple heuristic
	NewRepresentative* rep = new NewRepresentative(g, 0);

	//builds the problem
	rep->build();

	//solves the problem
	rep->solve();

	printf("Graph = %s \n SOLUTION = %ld \n LP SOLUTION = %f \n TIME = %f \n NUMBER OF NODES = %ld \n GAP = %f\n", argv[1], rep->getSolution(), rep->getLPsolution(), rep->getElapsedTime(), rep->getNnodes(), rep->getGap());
	fprintf(fout,"%s \t %ld \t %f \t %f \t %ld \t %f \n", argv[1], rep->getSolution(), rep->getLPsolution(), rep->getElapsedTime(), rep->getNnodes(), rep->getGap());

	return 0;
}

