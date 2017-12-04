/*
 * Heuristic.cpp
 *
 *  Created on: 8 de jan de 2017
 *      Author: mcsma
 */

#include "Heuristic.h"

// an generic greedy algorithm to finished up coloring
void Heuristic::greedyAlgorithm(){
	//define the uncolored vertices
	Set* uncolored = new Set(n);
	uncolored->removeAll();
	for(int i = 0; i < szcl; i++){
		uncolored->unio(colours[i]);
	}
	uncolored->complement();

	int v, color, i;
	bool colored;

	while(!uncolored->isEmpty()){
		//get the firts uncolored vertex
		v = uncolored->firstElem();
		uncolored->remove(v);

		colored = false;
		color = 0;
		i = 0;
		//look for a color for v
		while(!colored && i < szcl){
			//Is there an neigbour of v colored with that color?
			if(g->getNeig(v)->isIntersEmpty(colours[i])){
				colours[i]->add(v);
				colored = true;
			}
			i++;
		}
		//if we could not find a color for v
		if(!colored){
			szcl++;
			colours[szcl]->add(v);
		}
	}
}

// the b coloring algorithm to verify that the b-coloring indeed respect all the constraints
void Heuristic::algoB(){
	Set* colenum = new Set(n);
	Set* aux;

	long v;

	bool bcolor;
	bool bv;
	long current;

	//begin the search for the end
	current = szcl-1;
	while(current >= 0){

		colenum->removeAll();
		colenum->unio(colours[current]);
		v = 0;
		bcolor = false;
		//verify if the current color has a b-vertex
		while(!colenum->isEmpty() && !bcolor){
			bv = true;
			v = colenum->firstElemAfter(v);
			colenum->remove(v);
			for(int j = 0; j < szcl; j++){
				if(current!=j){
					if(g->getNeig(v)->isIntersEmpty(colours[j])){
						bv = false;
					}
				}
			}
			if(bv) bcolor = true;
		}

		int j = 0;
		//if the current color has no b-vetex, eliminate the color
		if(!bcolor){
			colenum->removeAll();
			colenum->unio(colours[current]);
			v = 0;
			while(!colenum->isEmpty()){
				v = colenum->firstElemAfter(v);
				colenum->remove(v);
				bv = true;
				j = 0;
				while(bv && j < szcl){
					if(current!=j){
						if(g->getNeig(v)->isIntersEmpty(colours[j])){
							colours[j]->add(v);
							colours[current]->remove(v);
							bv = false;
						}
					}
					j++;
				}
			}

			//rearrange the vector of color classes
			aux = colours[current];
			for(int i = current; i < szcl-1; i++){
				colours[i] = colours[i+1];
			}
			colours[szcl-1] = aux;
			szcl--;
		}
		current--;
	}


}

//Initializes the interface
Heuristic::Heuristic(Graph* h) {
	szcl = 0;
	tm = new Timer();
	g = h;
	n = g->sizeV();
	colours = new Set*[n];
	for(int i = 0; i < n; i++){
		colours[i] = new Set(n);
	}
	elapsedtm = 0;
}

//Destroy the interface
Heuristic::~Heuristic() {
	for(int i = 0; i < n; i++){
		delete colours[i];
	}
	delete colours;
	delete tm;
}

//Interface to the solver
void Heuristic::solve() {
	tm->start();
	innerSolver();
	elapsedtm = tm->stop();
}

//Retrive the optimal solution
long Heuristic::getSolution() {
	return szcl;
}

Set* Heuristic::getSolutionColor(int i){
	if(i < szcl) return colours[i];
	else return NULL;
}

//Retrive the elapsed time to solve the problem
float Heuristic::getElapsedTime() {
	return elapsedtm;
}

void Heuristic::print(){
	printf("NUMBER OF COLORS = %ld \n", szcl);
	for(long int i = 0; i < szcl; i++){
		printf("COLOR %ld = ", i+1);
		for(long int j = 0; j < n; j++){
			if(colours[i]->isIn(j)) printf(" %ld ", j+1);
		}
		printf("\n");
	}
}
