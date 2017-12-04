/*
 * Main_heu.c
 *
 *  Created on: 25 de out de 2017
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
	Heuristic* solver;
	Heuristic* solver2;

	printf("TESTING GRAPH %s \n", argv[1]);

	//an simple heuristic
	solver = new BasicHeuristic(g);
	solver2 = new TrivialHeuristic(g);

	solver->solve();

	//solves the problem
	solver2->solve();

	printf("Graph = %s \n SOLUTION HEU1 = %ld \n SOLUTION HEU2 = %ld \n TIME HEU1 = %f \n TIME HEU2 = %f \n", argv[1], solver->getSolution(), solver2->getSolution(), solver->getElapsedTime(),solver2->getElapsedTime());
	fprintf(fout,"%s \t %ld \t %ld \t %f \t %f \n",  argv[1], solver->getSolution(), solver2->getSolution(), solver->getElapsedTime(),solver2->getElapsedTime());

	return 0;
}



