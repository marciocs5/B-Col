/*
 * Heuristic.h
 *
 *  Created on: 8 de jan de 2017
 *      Author: mcsma
 */

#ifndef SRC_SOLVER_HEURISTIC_H_
#define SRC_SOLVER_HEURISTIC_H_

#include "../tools/Set.h"
#include "../tools/Timer.h"
#include "../tools/Graph.h"
#include <cstdio>

/*
 * An generic class to handle the heuristics to the b-coloring problem
 *
 * */
class Heuristic {
protected:

	long szcl;// the number of colours used in this method

	Timer* tm;//the clock

	Set** colours;// the adjacent matrix representing the given coloration

	long n;

	float elapsedtm;

	Graph* g; //the graph

	/*
	 * Completely or partialy color the graph associated to the current object
	 * */
	virtual void innerSolver() = 0;

	/*
	 * An generic greedy coloring algorithm, this algorithm expands any partial color to a complete color
	 * */
	void greedyAlgorithm();

	/*
	 * An generic b coloring algorithm, this algorithm turns any coloring of the graph into a b-coloring
	 * */
	void algoB();

public:
	/*
	 * Build an heuristic to color the graph passed as input
	 *
	 * @param h the graph
	 * */
	Heuristic(Graph* h);

	/*
	 * Destroy this object
	 * */
	virtual ~Heuristic();

	/* INTERFACE
	 * Completely or partialy color the graph associated to the current object
	 * */
	void solve();

	/*
	 * Retrivies the value of the optimal solution founded by the heuristic represented
	 * by this objetc
	 *
	 * @return the value of the solution built by the concrete object
	 * */
	long getSolution();

	/*
	 * Retrivies the set of vertices colored with color i in the optimal solution
	 * founded by the heuristic represented by this object
	 *
	 * @return the value of the solution built by the concrete object
	 * */
	Set* getSolutionColor(int i);

	/*
	 * Retrivies the elapsed time spend in the calculus
	 *  of the optimal solution founded by the heuristic represented
	 * by this object
	 *
	 * @return the elapsed time in the computation of the solution built by the concrete object
	 * */
	float getElapsedTime();

	/* A printer for this object */
	void print();

};

#endif /* SRC_SOLVER_HEURISTIC_H_ */
