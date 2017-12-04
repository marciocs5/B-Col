/*
 * Graph.h
 *
 *  Created on: 19 de dez de 2016
 *      Author: marcio
 */

#ifndef SRC_TOOLS_GRAPH_H_
#define SRC_TOOLS_GRAPH_H_

#include "Set.h"
#include <cstdio>

/*A simple graph represented by its adjacent matrix. We assume all vertices are
 * indexed by a natural number and the vertex set of the graph is a continuos sequel*/
class Graph {
private:

	long n; // number of vertices
	long m; // number of edges

	Set** edges; //the adjacent matrix of the graph

	Graph();

public:
	/*
	 * Build an empty graph with n vertices.
	 *
	 * @param n the number of vertices in the graph.
	 * @return a empty graph with n vertices.
	 */
	Graph(long n);

	/*
	 * Destructor of the graph class
	 *
	 */
	virtual ~Graph();

	/*
	 * Retrivies the number of edges of the graph.
	 *
	 * @return the number of edges of the graph.
	 *
	 */
	long sizeE();

	/*
	 * Retrivies the number of vertices of the graph.
	 *
	 * @return the number of vertices of the graph.
	 *
	 */
	long sizeV();

	/*
	 * Add the edge (uv) to the graph. If both, u and v are smaller than n;
	 * otherwise this function does nothing.
	 *
	 * @param v an integer smaller than n representing the first vertex.
	 * @param u an integer smaller than n representing the second vertex.
	 *
	 */
	void addEdge(long v, long u);

	/*
	 * Remove the edge (uv) to the graph. If both, u and v are smaller than n;
	 * otherwise this function does nothing.
	 *
	 * @param v an integer smaller than n representing the first vertex.
	 * @param u an integer smaller than n representing the second vertex.
	 *
	 */
	void removeEdge(long v, long u);

	/*
	 * Verify whether the edge (uv) is a part of the graph.
	 *
	 * @param v an integer smaller than n representing the first vertex.
	 * @param u an integer smaller than n representing the second vertex.
	 *
	 * @return if (uv) is in the current graph return true; otherwise return false.
	 */
	bool hasEdge(long v, long u);

	/*
	 * Retrivies the neighbourhood of the vertex given as input.
	 *
	 * @param v an integer smaller than n representing the vertex.
	 *
	 * @return an Set object representing the neighbourhood of the vertex v. if
	 * v is bigger than n or negative this functions will return an empty set.
	 */
	Set* getNeig(long v);

	/*
	 * Retrivies the antineighbourhood of the vertex given as input.
	 *
	 * @param v an integer smaller than n representing the vertex.
	 *
	 * @return an Set object representing the antineighbourhood of the vertex v. if
	 * v is bigger than n or negative this functions will return an empty set.
	 */
	Set* getAntiNeig(long v);

	/*
	 * Retrivies the degree of the vertex given as input.
	 *
	 * @param v an integer smaller than n representing the vertex.
	 *
	 * @return the degreee of the vertex v. if
	 * v is bigger than n or negative this functions will return 0.
	 */
	long degree(long v);

	/*
	 * Retrivies the degree of the vertex given as input.
	 *
	 * @param v an integer smaller than n representing the vertex.
	 *
	 * @return the degreee of the vertex v. if
	 * v is bigger than n or negative this functions will return 0.
	 */
	long degreeRest(long v, Set* subset);

	Graph* copy();

	/*
	 * A graphical representation of the graph
	 * */
	void print();

};

#endif /* SRC_TOOLS_GRAPH_H_ */
