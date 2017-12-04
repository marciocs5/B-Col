/*
 * main_porta.c
 *
 *  Created on: 11 de out de 2017
 *      Author: marcio
 */

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
#include "Reader.h"
#include <cstdio>
#include <zlib.h>

void buildIntro(FILE* fout, Graph* g, int var){
	fprintf(fout,"DIM=%d \n", var);

	Heuristic* heu = new BasicHeuristic(g);
	heu->solve();

	fprintf(fout,"VALID \n");
	for(int i = 0; i < g->sizeV(); i++){
		fprintf(fout,"1 ");
	}
	for(int i = g->sizeV(); i < var; i++){
		fprintf(fout,"0 ");
	}
	fprintf(fout,"\n\n");



	fprintf(fout,"LOWER_BOUNDS\n");
	for(int i = 0; i < var; i++){
		fprintf(fout,"0 ");
	}
	fprintf(fout,"\n");

	fprintf(fout,"UPPER_BOUNDS\n");
	for(int i = 0; i < var; i++){
		fprintf(fout,"1 ");
	}
	fprintf(fout,"\n\n");

	fprintf(fout,"ELIMINATION_ORDER\n");
	for(int i = 0; i < var; i++){
		fprintf(fout,"%d ", i+1);
	}
	fprintf(fout,"\n\n");

	fprintf(fout,"INEQUALITIES_SECTION\n");
}

void addEdgeConst(FILE* fout, long v, long u, long w, Graph* g, int** x){
	fprintf(fout, "+x%d +x%d -x%d <= 0\n", x[v][u], x[v][w],x[v][v]);
}

void addSingleVConst(FILE* fout, long v, long u, Graph* g, int** x){
	fprintf(fout, "+x%d -x%d <= 0\n", x[v][u],x[v][v]);
}

void addRepresentativeConst(FILE* fout, long v, Graph* g, int** x){
	fprintf(fout, "+x%d ",x[v][v]);

	for(int i = 0; i < g->sizeV(); i++){
		if(i != v && !g->hasEdge(v, i) && x[i][i] >= 0){
			fprintf(fout, "+x%d ",x[i][v]);
		}
	}

	fprintf(fout, "== 1\n ");
}

void addBcolConstraint(FILE* fout, long v, long u, Graph* g, int** x){
	fprintf(fout, "+x%d ",x[v][v]);
	fprintf(fout, "+x%d ",x[u][u]);

	for(int i = 0; i < g->sizeV(); i++){
		if(i != v && i != u && !g->hasEdge(u, i) && g->hasEdge(v, i)){
			fprintf(fout, "-x%d ",x[u][i]);
		}
	}

	fprintf(fout, "<= 1\n ");
}

int main(int argc, char **argv){

	//input file
	std::ifstream ifs (argv[1], std::ifstream::in);
	//output file
	FILE* fout = fopen(argv[2], "w");
	FILE* fout2 = fopen(argv[3], "w");

	//the reader for the graph
	Reader myReader;

	//the graph
	Graph * g = myReader.read(ifs);

	int n = g->sizeV();
	int var = 1;
	int** x = new int*[n];
	for(int i = 0; i < n; i++){
		x[i] = new int[n];
		for(int j = 0; j < n; j++){
			x[i][j] = -1;
		}
	}

	for(int i = 0; i < n; i++){
		x[i][i] = var++;
		fprintf(fout2,"%d \t %d \t %d \n", i+1, i+1, var-1);
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j< n; j++){
			if(j != i && !g->hasEdge(i, j)){
				x[i][j] = var++;
				fprintf(fout2,"%d \t %d \t %d \n", i+1, j+1, var-1);
			}
		}
	}

	buildIntro(fout, g, var);

	Set* visited = new Set(n);
	long u, w;
	Set* mark = new Set(n);
	for(int v = 0; v < n; v++){
		addRepresentativeConst(fout, v, g, x);

		visited->removeAll();
		visited->unio(g->getAntiNeig(v));
		u = 0;
		mark->removeAll();
		while(!visited->isEmpty()){
			u = visited->firstElemAfter(u);
			w = visited->firstElemAfter(u+1);
			while(w < n){
				if(g->hasEdge(w, u)){
					addEdgeConst(fout, v, u, w, g, x);
					mark->add(u);
					mark->add(w);
				}
			w = visited->firstElemAfter(w+1);
			}

			if(!mark->isIn(u)) addSingleVConst(fout, v, u, g, x);
				visited->remove(u);
		}
	}

	for(int v = 0; v < n; v++){
		for(int u = 0; u < n; u++){
			if(v!=u && x[v][v] >= 0 && x[u][u] >= 0 && !g->hasEdge(v, u)) addBcolConstraint(fout, v, u, g, x);
		}
	}

	fprintf(fout, "\nEND\n ");
	fclose(fout);
	fclose(fout2);

	return 0;
}




