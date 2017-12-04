/*
 * Graph.cpp
 *
 *  Created on: 19 de dez de 2016
 *      Author: marcio
 */

#include "Graph.h"

#include <cstdlib>

Graph::Graph(){
	n = 0; // number of vertices
	m = 0; // number of edges

	edges = NULL;

}

//build a empty graph with n nodes
Graph::Graph(long n){
	this->n = n; // number of vertices
	m = 0; // number of edges

	edges = new Set*[n];
	for(int i = 0; i < n; i++) edges[i] = new Set(n);
}

//destroy the given graph
Graph::~Graph(){
	for(int i = 0; i < n; i++) delete edges[i];
	delete edges;
}

long Graph::sizeE(){
	return m;
}

long Graph::sizeV(){
	return n;
}

//add an edge between u and v
void Graph::addEdge(long v, long u){
	if(v < n && u < n){
		edges[v]->add(u);
		edges[u]->add(v);
		m++;
	}
}

//add an edge between v and u
void Graph::removeEdge(long v, long u){
	if(v < n && u < n){
		edges[v]->remove(u);
		edges[u]->remove(v);
		m--;
	}
}

//verify if there is an edge between v and u
bool Graph::hasEdge(long v, long u){
	if(v < n && u < n) return edges[v]->isIn(u);
	else return false;
}

//gets the neighboors of v
Set* Graph::getNeig(long v){
	Set* ret = new Set(n);
	if(v < n){
		ret->unio(edges[v]);
	}
	return ret;
}

//gets the antineighboors of v
Set* Graph::getAntiNeig(long v){
	Set* ret = new Set(n);
	if(v < n){
		ret->unio(edges[v]);
	}
	ret->complement();
	ret->remove(v);
	return ret;
}

//gets the degree of the vertex v
long Graph::degree(long v){
	if(v < n) return edges[v]->count();
	else return 0;
}

long Graph::degreeRest(long v, Set* subset){
	if(v < n)
		return edges[v]->countRest(subset);
	else return 0;
}

Graph* Graph::copy(){
	Graph* g = new Graph();

	g->n = n; // number of vertices
	g->m = 0; // number of edges

	g->edges = new Set*[n];
	for(int i = 0; i < n; i++) g->edges[i] = new Set(n);

	for(long i = 0; i < n; i++){
		for(long j = i+1; j < n; j++){
			if(hasEdge(i, j)){
				g->edges[i]->add(j);
				g->edges[j]->add(i);
				g->m++;
			}
		}
	}

	return g;
}

//print the graph
void Graph::print(){
	printf("NUMBER OF VERTICES: %ld \n", n);
	printf("NUMBER OF EDGES: %ld \n", m);
	printf("GRAPH:\n");
	for(long int i = 0; i < n; i++){
		printf("N(%ld):", i+1);
		for(long int j = 0; j < n; j++){
			if(hasEdge(i, j))printf("|%ld|", j+1);
		}
		printf("\n");
	}
}
