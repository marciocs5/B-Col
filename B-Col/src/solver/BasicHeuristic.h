/*
 * BasicHeuristic.h
 *
 *  Created on: 26 de jan de 2017
 *      Author: marcio
 */

#ifndef SRC_SOLVER_BASICHEURISTIC_H_
#define SRC_SOLVER_BASICHEURISTIC_H_

#include "Heuristic.h"
#include <algorithm>    // std::swap

class BasicHeuristic: public Heuristic {
protected:
	// the unceolored vertices
	Set* uncolored;

	/*
	 * Order the vertices of the graph according to their degree.
	 * */
	void orderVertices(long* ov, long* dg);

	/*
	 * Select the vertices that are neighbours to at least two b-vertices.
	 *
	 * @param a pointer to be fulfilled with the list L.
	 *
	 * @return the cardinality of the list L.
	 *
	 * */
	long selectLlist(long* llist);

	/*
	 * Select the vertices that are suitable candidates to be b-vertices.
	 *
	 * @return the cardinality of the list of b-vertices candidates
	 *
	 * */
	long choseBV(long* ov, long* dg);

	/*
	 * Completely or partialy color the graph associated to the current object
	 * */
	void innerSolver();

public:
	/*
	 * Build an heuristic to color the graph passed as input
	 *
	 * @param h the graph
	 * */
	BasicHeuristic(Graph* h);

	/*
	 * Destroy this object
	 * */
	virtual ~BasicHeuristic();
};

#endif /* SRC_SOLVER_BASICHEURISTIC_H_ */
