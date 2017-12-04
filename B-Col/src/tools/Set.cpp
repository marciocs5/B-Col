/*
 * Set.cpp
 *
 *  Created on: 19 de dez de 2016
 *      Author: marcio
 */

#include "Set.h"

//build a emptyset with size "size"
Set::Set(int sz){
	size = sz;
	elems = new bool[sz];
	for(int i = 0; i < sz; i++) elems[i] = false;
}

//destroy the sets
Set::~Set(){
	delete elems;
}

//add elem to the set
void Set::add(long elem){
	if(elem < size) elems[elem] = true;
}

//add all posible elems
void Set::addAll(){
	for(int i = 0; i < size; i++) elems[i] = true;
}

//remove elem of the set
void Set::remove(long elem){
	if(elem < size) elems[elem] = false;
}

//remove all the elems of the set
void Set::removeAll(){
	for(int i = 0; i < size; i++) elems[i] = false;
}

//verify if the elem is in the set or not
bool Set::isIn(long elem){
	return elems[elem];
}

void Set::complement(){
	for(int i = 0; i < size; i++){
		elems[i] = !elems[i];
	}
}

Set* Set::copy(){
	Set* ret = new Set(size);
	for(int i = 0; i < size; i++){
		ret->elems[i] = elems[i];
	}
	return ret;
}

bool Set::isEqual(Set* s){
	bool ret = true;
	for(int i = 0; i < size; i++) if(s->elems[i] != elems[i]) ret = false;
	return ret;
}

//intersects the current set with the set s
void Set::inter(Set* s){
	for(int i = 0; i < size; i++) elems[i] &= s->elems[i];
}

//subtracts the set s from the current set
void Set::subtr(Set* s){
	for(int i = 0; i < size; i++)
		if(elems[i] && s->elems[i]) elems[i] = false ;
}

//add all elements of the set s into the current set
void Set::unio(Set* s){
	for(int i = 0; i < size; i++) elems[i] |= s->elems[i];
}

//returns the first element of the set
long Set::firstElem(){
	for(int i = 0; i < size; i++)
		if(elems[i]) return i;
	return size + 1;
}

//returns the first element of the set greater ot equals to elem
long Set::firstElemAfter(long elem){
	for(int i = elem; i < size; i++)
		if(elems[i]) return i;
	return size + 1;
}

//returns the number of bits settled in 1
long Set::count(){
	int count = 0;
	for(int i = 0; i < size; i++) if(elems[i]) count++;
	return count;
}

long Set::countRest(Set* subset){
	int count = 0;
	for(int i = 0; i < size; i++) if(elems[i] && subset->elems[i]) count++;
	return count;
}

bool Set::isEmpty(){
	bool isin = true;
	for(int i = 0; i < size; i++){
		if(elems[i]) isin = false;
	}
	return isin;
}

bool Set::isUnionEmpty(Set* s){
	bool ret = true;
	for(int i = 0; i < size; i++){
		if(elems[i] || s->elems[i])
			ret = false ;
	}
	return ret;
}

bool Set::isIntersEmpty(Set* s){
	bool ret = true;
	for(int i = 0; i < size; i++){
		if(elems[i] && s->elems[i])
			ret = false;
	}
	return ret;
}

bool Set::isSubtEmpty(Set* s){
	bool ret = true;
	for(int i = 0; i < size; i++){
		if(elems[i] * s->elems[i])
			ret = false;
	}
	return ret;
}

void Set::print(){
	printf("SET size = %ld\n", size);
	for(long i = 0; i < size; i++){
		if(elems[i]) printf(" %ld ", i+1);
	}
	printf("\n");
}
