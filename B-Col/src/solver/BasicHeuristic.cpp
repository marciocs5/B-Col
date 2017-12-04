/*
 * BasicHeuristic.cpp
 *
 *  Created on: 26 de jan de 2017
 *      Author: marcio
 */

#include "BasicHeuristic.h"

void BasicHeuristic::orderVertices(long* ov, long* dg){

	//initialize the vectors
	for(int i = 0; i < n; i++){
		ov[i] = i;
		dg[i] = g->degree(i);
	}

	//order the vertices according to the degree
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(dg[i] < dg[j]){
				std::swap(dg[i], dg[j]);
				std::swap(ov[i], ov[j]);
			}
		}
	}

}

long BasicHeuristic::selectLlist(long* llist){
	long lsize = 0;

	long* vt = new long[n];
	long* cn = new long[n];

	//initialize the vectors
	for(int i = 0; i < n; i++){
		vt[i] = i;
		cn[i] = 0;
	}

	//remove the vertices already colored of the L list
	for(int i = 0; i < n; i++){
		for(int j = 0; j < szcl; j++){
			if(colours[j]->isIn(i)) cn[i] = -n-1;
		}
	}


	//counts the number of adjacent colors for every vertice
	for(int i = 0; i < n; i++){
		for(int j = 0; j < szcl; j++){
			if(!colours[j]->isIntersEmpty(g->getNeig(i))) cn[i]++;
		}
	}

	//order the vertices
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(cn[i] < cn[j]){
				std::swap(cn[i], cn[j]);
				std::swap(vt[i], vt[j]);
			}
		}
	}

	//determine the size and the L list
	for(int i = 0; i < n; i++){
		if(cn[i] > 0){
			llist[lsize++] = vt[i];
		}
	}

	return lsize;
}

long BasicHeuristic::choseBV(long* ov, long* dg){
	long mdegree = 0;

	for(int i = 0; i < n; i++)if(dg[i] >= i-1) mdegree = i;

	szcl = 0;
	for(int i = 0; i < mdegree; i++){
		colours[szcl++]->add(i);
		uncolored->remove(i);
	}

	return mdegree;
}

/*
 * Completely or partialy color the graph associated to the current object
 * */
void BasicHeuristic::innerSolver(){
	long* ov = new long[n];
	long* dg = new long[n];

	orderVertices(ov, dg);

	long mdg = choseBV(ov, dg);

	long* llist = new long[n];
	long szl = selectLlist(llist);
	long cl;

	//Colors all the elements in the list L
	for(int i = 0; i < szl; i++){
		cl = 0;
		while(cl < szcl){
			if(colours[cl]->isIntersEmpty(g->getNeig(llist[i]))){
				colours[cl]->add(llist[i]);
				cl = szcl+1;
				uncolored->remove(llist[i]);
			}else cl++;
		}
	}

	//Color the rest of the neigbood of each vertex
	Set* aux = new Set(n);
	Set* colneg = new Set(szcl);
	long auxv;
	long givencolor;
	for(int i = 0; i < mdg; i++){
		colneg->addAll();
		for(int j = 0; j < szcl; j++){
			if(!colours[j]->isIntersEmpty(g->getNeig(ov[i]))) colneg->remove(j);
		}

		aux->removeAll();
		aux->unio(uncolored);
		aux->subtr(g->getNeig(ov[i]));
		while(!aux->isEmpty()){
			auxv = aux->firstElem();
			aux->remove(auxv);
			//we assume that auxv is removed from the uncolored list even if it is not colored
			uncolored->remove(auxv);
			givencolor = colneg->firstElem();
			while(givencolor < szcl && !colours[givencolor]->isIntersEmpty(g->getNeig(auxv))){
				givencolor = colneg->firstElemAfter(givencolor + 1);
			}
			if(givencolor < szcl){
				colneg->remove(givencolor);
				colours[givencolor]->add(auxv);
			}
		}
	}

	//color all the uncolored vertices
	greedyAlgorithm();

	//verify the final b coloring
	algoB();


}

BasicHeuristic::BasicHeuristic(Graph* h): Heuristic(h) {
	uncolored = new Set(n);
	uncolored->addAll();
}

BasicHeuristic::~BasicHeuristic() {
	delete uncolored;
}

