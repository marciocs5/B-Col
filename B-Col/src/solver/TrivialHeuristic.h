/*
 * TrivialHeuristic.h
 *
 *  Created on: 21 de mar de 2017
 *      Author: marcio
 */

#ifndef SRC_SOLVER_TRIVIALHEURISTIC_H_
#define SRC_SOLVER_TRIVIALHEURISTIC_H_

#include "Heuristic.h"
#include <algorithm>    // std::swap

/**
 * The most trivial heuristic for the b-coloring problem. The process began by given a different
 * color to each vertex and then apply the B algorithm untill we arrive in a valid b-coloring.
 *
 * */
class TrivialHeuristic: public Heuristic {
protected:

	/*
	 * Completely or partialy color the graph associated to the current object. The process began by given
	 * a different color to each vertex and then apply the B algorithm untill we arrive in a valid b-coloring.
	 * */
	void innerSolver();

public:
	/*
	 * The construtor
	 * */
	TrivialHeuristic(Graph* h);

	/*
	 * The destructor
	 * */
	virtual ~TrivialHeuristic();
};

#endif /* SRC_SOLVER_TRIVIALHEURISTIC_H_ */
