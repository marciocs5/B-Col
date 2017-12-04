/*
 * Solver.cpp
 *
 *  Created on: 19 de dez de 2016
 *      Author: marcio
 */

#include "Solver.h"

//Constructor
Solver::Solver(Graph* h){
	g = h;
	tm = new Timer();
	elapsedtm = 0.0;
	solution = 0.0;
	num_var = 0;
	nnodes = 0;
	gap = 100.0;
}

//Destructor
Solver::~Solver(){
	delete tm;
}

//Generic builder, initialize all the inner variables
void Solver::build(){
	innerbuild();
}

//Generic solve, update the current solution and the elapsed time
void Solver::solve(){
	tm->start();
	innerSolver();
	elapsedtm = tm->stop();
}

//Retrieves the optimal solution
long Solver::getSolution(){
	return solution;
}

//Retrieves the elapsed time
float Solver::getElapsedTime(){
	return elapsedtm;
}

double Solver::getLPsolution(){
	return solutionLP;
}

long Solver::getNnodes(){
	return nnodes;
}

long Solver::getNVars(){
	return num_var;
}

double Solver::getGap(){
	return gap;
}
