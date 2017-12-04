/*
 * ImpRepresentative.h
 *
 *  Created on: 8 de jan de 2017
 *      Author: mcsma
 */

#ifndef SRC_SOLVER_IMPREPRESENTATIVERELAX_H_
#define SRC_SOLVER_IMPREPRESENTATIVERELAX_H_

#include <ilcplex/cplex.h>
#include <stdlib.h>
#include <string.h>
#include "Solver.h"

/*
 * Class representing an Solver based in the representative formulation for the
 * b-coloring problem
 * */
class ImpRepresentativeRelax: public Solver{
protected:
	//the cplex enviroment
	CPXENVptr env = NULL;

	//the cplex problem
	CPXLPptr lp = NULL;

	//a map for the variables
	long** x;

	//a lower bound to the optimal solution
	long lb;

	//the number of vertices
	long n;

	//the number of variables
	long var;

	//if we add the users cuts or not
	bool addcuts;

	/*
	 * Initializes the variables and builds the cplex model
	 * */
	void innerbuild();

	/*
	 * Solve the model and write the solution in the variable solution of the class Solver
	 * */
	void innerSolver();

	/*
	 * Creates a binary variable with coeficient coef, called name
	 *
	 * @param coef the coeficient of this variable in the onjective function
	 * @param name the name of the variable
	 * */
	void addBinVar(double coef, char* name);

	/*
	 * Add the constraint x_{v,u} + x_{v,w} <= x_{v,v} to the model
	 *
	 * @param v the representative vertices
	 * @param u a vertex in the anti-neigbourhood of v
	 * @param w a vertex in the anti-neigbourhood of v
	 * */
	void addEdgeConst(long v, long u, long w);

	/*
	 * Add the constraint x_{v,u} <= x_{v,v} to the model
	 *
	 * @param v the representative vertices
	 * @param u a vertex in the anti-neigbourhood of v
	 * */
	void addSingleVConst(long v, long u);

	/*
	 * Add the representative
	 * */
	void addRepresentativeConst(long v);

	/*
	 *
	 * */
	void addBcolConstraint(long v, long u);


	void addCutConstraint(long v, long u, long w);

public:
	/*
	 *
	 * */
	ImpRepresentativeRelax(Graph* g, long lb, bool addcuts);

	/*
	 *
	 * */
	virtual ~ImpRepresentativeRelax();
};

#endif /* SRC_SOLVER_IMPREPRESENTATIVE_H_ */
