/*
 * TrivialHeuristic.cpp
 *
 *  Created on: 21 de mar de 2017
 *      Author: marcio
 */

#include "TrivialHeuristic.h"

void TrivialHeuristic::innerSolver(){
	long n = g->sizeV();
	szcl = 0;
	//each vertex has a different color
	for(int i = 0; i < n; i++){
		colours[szcl++]->add(i);
	}
	//verify the final b coloring
	algoB();
}

TrivialHeuristic::TrivialHeuristic(Graph* h): Heuristic(h){}

TrivialHeuristic::~TrivialHeuristic() {}

