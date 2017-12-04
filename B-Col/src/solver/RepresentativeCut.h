/*
 * ImpRepresentative.h
 *
 *  Created on: 8 de jan de 2017
 *      Author: mcsma
 */

#ifndef SRC_SOLVER_IMPREPRESENTATIVECUT_H_
#define SRC_SOLVER_IMPREPRESENTATIVECUT_H_

#include <ilcplex/cplex.h>
#include <stdlib.h>
#include <string.h>
#include "Solver.h"
#include "ImpRepresentative.h"

/*
 * Class representing an Solver based in the representative formulation for the
 * b-coloring problem
 * */
class RepresentativeCut: public Solver, public ImpRepresentative{
protected:

	/*
	 * Initializes the variables and builds the cplex model
	 * */
	void innerbuild();

public:
	/*
	 *
	 * */
	RepresentativeCut(Graph* g, long lb);

	/*
	 *
	 * */
	virtual ~RepresentativeCut();
};

#endif /* SRC_SOLVER_IMPREPRESENTATIVE_H_ */
