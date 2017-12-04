/*
 * ImpRepresentative.cpp
 *
 *  Created on: 8 de jan de 2017
 *      Author: mcsma
 */

#include "ImpRepresentative.h"

void RepresentativeCut::innerbuild(){
	int status;
	env = CPXopenCPLEX(&status);
	lp = CPXcreateprob(env, &status, "B-col with lower bounds");

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			x[i][j] = -1;
		}
	}
	//printf("INIT OK!\n");
	//getchar();

	char name[100];
	for(int i = 0; i < n; i++){
		if(g->degree(i) >= lb - 1){
			//printf("vertice %d passed \n", i);
			//getchar();
			x[i][i] = var++;
			sprintf(name, "x[%d][%d]", i+1, i+1);
			addBinVar(1.0, name);
			for(int j = 0; j< n; j++){
				if(j != i && !g->hasEdge(i, j)){
					x[i][j] = var++;
					sprintf(name, "x[%d][%d]", i+1, j+1);
					addBinVar(0.0, name);
				}
			}
		}
	}
	//printf("BUILD OK!\n");
	//getchar();

	Set* visited = new Set(n);
	long u, w;
	Set* mark = new Set(n);
	for(int v = 0; v < n; v++){
		addRepresentativeConst(v);
		//printf("Representative OK for %d\n", v);
		//getchar();
		visited->removeAll();
		visited->unio(g->getAntiNeig(v));
		u = 0;
		mark->removeAll();
		while(!visited->isEmpty()){
			u = visited->firstElemAfter(u);
			w = visited->firstElemAfter(u+1);
			while(w < n){
				if(g->hasEdge(w, u)){
					addEdgeConst(v, u, w);
					mark->add(u);
					mark->add(w);
				}
				w = visited->firstElemAfter(w+1);
			}

			if(!mark->isIn(u)) addSingleVConst(v, u);

			visited->remove(u);
		}
	}

	for(int v = 0; v < n; v++){
		for(int u = 0; u < n; u++){
			if(v!=u && x[v][v] >= 0 && x[u][u] >= 0 && !g->hasEdge(v, u)) addBcolConstraint(v, u);
		}
	}
}

RepresentativeCut::RepresentativeCut(Graph* h, long lnb): Solver(h), ImpRepresentative(h, lnb){

}

ImpRepresentative::~ImpRepresentative(){ }

