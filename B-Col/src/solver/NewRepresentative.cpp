/*
 * NewRepresentative.cpp
 *
 *  Created on: 30 de out de 2017
 *      Author: marcio
 */

#include "NewRepresentative.h"

int myheuristicfunc2(CPXCENVptr env, void *cbdata, int wherefrom, void *cbhandle, double *objval_p, double *x, int *checkfeas_p, int *useraction_p){
	int* result_p = new int;
	CPXgetcallbackinfo(env, cbdata, wherefrom, CPX_CALLBACK_INFO_NODE_COUNT, (void*)result_p);

	if((*result_p) == 0){
		*((double*)cbhandle) = *objval_p;
	}
	*useraction_p = 0;
	return 0;
}

void NewRepresentative::innerbuild(){
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
		for(int j = 0; j< n; j++){
			if(j != i && !g->hasEdge(i, j)){
				x[i][j] = var++;
				sprintf(name, "x[%d][%d]", i+1, j+1);
				addBinVar(1.0, name);
			}
		}
	}
	//printf("BUILD OK!\n");
	//getchar();

	Set* visited = new Set(n);
	long u, w;
	Set* mark = new Set(n);
	for(int v = 0; v < n; v++){
		//addRepresentativeConst(v);
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
			if(v!=u && !g->hasEdge(v, u)) addBcolConstraint(v, u);
		}
	}
}

void NewRepresentative::innerSolver(){
	CPXchgprobtype(env, lp, 1);

	CPXchgobjsen(env, lp, CPX_MIN);

	int status = CPXsetdblparam(env, CPX_PARAM_TILIM/*1039*/, 600.0);
	//if(status != 0){
	//	printf("\n PROBLEMS TO ADD TIME LIMIT TO THE MODEL!!!! ERRO CODE = %d\n", status);
	//}

	status = CPXwriteprob (env, lp, "bcolwithheuristic2.lp", NULL);
	if(status != 0){
		printf("\nPROBLEMS TO WRITE THE MODEL!!!! ERRO CODE = %d\n", status);
	}

	//to retrieve the LP solution
	double* mydata = new double;
	status = CPXsetheuristiccallbackfunc(env, myheuristicfunc2, (void*)mydata);

	status = CPXmipopt (env, lp);

	if(status != 0){
		printf("\n PROBLEMS TO SOLVE THE MODEL!!!! ERRO CODE = %d\n", status);
	}

	int lpstat = CPXgetstat (env, lp);
	if(lpstat != CPXMIP_OPTIMAL && lpstat != CPXMIP_OPTIMAL_TOL && lpstat != CPX_STAT_OPTIMAL  && lpstat != CPX_STAT_OPTIMAL_INFEAS){
		printf("\n No SOLUTION status = %d\n", lpstat);
	}

	double aux;
	CPXgetobjval(env, lp, &aux);
	if(status != 0){
		printf("\nPROBLEMS TO RETRIVE OPTIMAL SOLUTION!!!! ERRO CODE = %d\n", status);
	}
	solution = n - aux;

	solutionLP = n - *mydata;

	CPXgetmiprelgap(env, lp, &aux);
	gap = aux;

	nnodes = CPXgetnodecnt(env, lp);
}


void NewRepresentative::addBinVar(double coef, char* name){
	double obj = coef;
	double lb = 0.0;
	double up = 1.0;
	char type = 'B';
	CPXnewcols(env, lp, 1, &obj, &lb, &up, &type, &name);
}

void NewRepresentative::addEdgeConst(long v, long u, long w){
	double rhs = 1.0;// lado direito
	int nzcnt = 0; //numero de coeficientes nao zero
	char sense = 'L';

	int rmatind[n+3];
	double rmatval[n+3];

	rmatind[nzcnt] = x[v][u];
	rmatval[nzcnt++] = 1.0;
	rmatind[nzcnt] = x[v][w];
	rmatval[nzcnt++] = 1.0;

	for(int i = 0; i < n; i++){
		if(x[i][v] >= 0){
			rmatind[nzcnt] = x[i][v];
			rmatval[nzcnt++] = 1.0;
		}
	}

	int rmatbeg[2] = {0, nzcnt-1};

	CPXaddrows(env, lp, 0, 1, nzcnt, &rhs, &sense, rmatbeg,rmatind, rmatval, NULL, NULL);
}

void NewRepresentative::addSingleVConst(long v, long u){
	double rhs = 1.0;// lado direito
	int nzcnt = 0; //numero de coeficientes nao zero
	char sense = 'L';

	int rmatind[n+3];
	double rmatval[n+3];

	rmatind[nzcnt] = x[v][u];
	rmatval[nzcnt++] = 1.0;

	for(int i = 0; i < n; i++){
		if(x[i][v] >= 0){
			rmatind[nzcnt] = x[i][v];
			rmatval[nzcnt++] = 1.0;
		}
	}

	int rmatbeg[2] = {0, nzcnt-1};

	CPXaddrows(env, lp, 0, 1, nzcnt, &rhs, &sense, rmatbeg,rmatind, rmatval, NULL, NULL);
}


void NewRepresentative::addBcolConstraint(long v, long u){
	double rhs = 1.0;// lado direito
	int nzcnt = 0; //numero de coeficientes nao zero
	char sense = 'G';

	int rmatind[3*n];
	double rmatval[3*n];

	for(int i = 0; i < n; i++){
		if(x[i][v] >= 0){
			rmatind[nzcnt] = x[i][v];
			rmatval[nzcnt++] = 1.0;
		}
	}

	for(int i = 0; i < n; i++){
		if(x[i][u] >= 0){
			rmatind[nzcnt] = x[i][u];
			rmatval[nzcnt++] = 1.0;
		}
	}

	for(int i = 0; i < n; i++){
		if(i != v && i != u && !g->hasEdge(u, i) && g->hasEdge(v, i)){
			rmatind[nzcnt] = x[u][i];
			rmatval[nzcnt++] = 1.0;
		}
	}

	int rmatbeg[2] = {0, nzcnt-1};

	if(nzcnt > 0)CPXaddrows(env, lp, 0, 1, nzcnt, &rhs, &sense, rmatbeg,rmatind, rmatval, NULL, NULL);
}

NewRepresentative::NewRepresentative(Graph* h, long lnb): Solver(h){
	lb = lnb;
	g = h;
	n = g->sizeV();
	var = 0;
	x = new long*[n];
	for(int i = 0; i < n; i++){
		x[i] = new long[n];
	}
}

NewRepresentative::~NewRepresentative(){
	for(int i = 0; i < n; i++) delete x[i];

	delete x;
}


