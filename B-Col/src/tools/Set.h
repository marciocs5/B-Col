/*
 * Set.h
 *
 *  Created on: 19 de dez de 2016
 *      Author: marcio
 */

#ifndef SRC_TOOLS_SET_H_
#define SRC_TOOLS_SET_H_

#include<cstdio>

/**
 * Representation of a set of integer numbers. The representation is assume
 * to be a bit vector.
 * */
class Set {
private:
	bool* elems;// binary representation
	long size;//number of elements
public:
	/*
	 * Build a empty set representing the integers between 0 and size-1
	 *
	 * @param size the number of integers that can belong to the set.
	 *
	 * */
	Set(int size);

	/*
	 * Destructor
	 * */
	virtual ~Set();

	/*
	 * Add the integer elem to the current set,
	 * if it belongs to the interval represented by this object(smaller than size)
	 *
	 * @param elem the element to be added in the current set
	 * */
	void add(long elem);

	/*
	 * Add all the integer in the interval 0 to size-1 to the set
	 * */
	void addAll();

	/*
	 * Remove the integer elem in the current set,
	 * if it belongs to the interval represented by this object(smaller than size)
	 *
	 * @param elem the element to be removed from the current set.
	 * */
	void remove(long elem);

	/*
	 * Remove all the integer in the interval 0 to size-1 in the set
	 * */
	void removeAll();

	/*
	 * Verify if the integer elem is in the current set,
	 *
	 * @param elem the element to be tested
	 *
	 * @return true if elem belongs to the set and false otherwise.
	 * */
	bool isIn(long elem);

	/*
	 * Perform the intersection between the current set and the set given, assuming that
	 * s has the same size of the current set, if it is not the case, it will produce an error.
	 *
	 * @param s the given set to be intersected with the current one.
	 *
	 * */
	void inter(Set* s);

	/*
	 * Swaps for the complement of the current object.
	 *
	 * @param s the given set to be intersected with the current one.
	 *
	 * */
	void complement();

	Set* copy();

	bool isEqual(Set* s);

	/*
	 * Perform the isubtraction between the current set and the set given, assuming that
	 * s has the same size of the current set, if it is not the case, it will produce an error.
	 *
	 * @param s the given set to be subtracted with the current one.
	 *
	 * */
	void subtr(Set* s);

	/*
	 * Perform the union between the current set and the set given, assuming that
	 * s has the same size of the current set, if it is not the case, it will produce an error.
	 *
	 * @param s the given set to be joined with the current one.
	 *
	 * */
	void unio(Set* s);

	/*
	 * Retrivies the first element of the set represented by the object.
	 *
	 * @return the first element of the set, if the set is empty it will return size+1.
	 *
	 * */
	long firstElem();

	/*
	 * Retrivies the first element of the set equals or bigger than the given element.
	 *
	 * @param elem the given element
	 *
	 * @return the first element of the set equals or bigger than the given element,
	 * if such element does not exist, it will return size+1.
	 *
	 * */
	long firstElemAfter(long elem);

	/*
	 * Count the number of elements in the current set represented by this object.
	 *
	 * @return the number of elements in the current set represented by this object.
	 *
	 * */
	long count();

	long countRest(Set* subset);

	/*
	 * Verifies if the current set represented by this object is empty.
	 *
	 * @return true if the current set represented by this object is empty and false otherwise.
	 *
	 * */
	bool isEmpty();

	/*
	 * Verifies if the union of the given set with the current set represented by this object is empty.
	 *
	 * @return true if the union of the given set with the current set represented by this object is empty
	 * and false otherwise.
	 *
	 * */
	bool isUnionEmpty(Set* s);

	/*
	 * Verifies if the intersection of the given set with the current set represented by this object is empty.
	 *
	 * @return true if the intersection of the given set with the current set represented by this object is empty
	 * and false otherwise.
	 *
	 * */
	bool isIntersEmpty(Set* s);

	/*
	 * Verifies if the subtration of the given set with the current set represented by this object is empty.
	 *
	 * @return true if the subtratcion of the given set with the current set represented by this object is empty
	 * and false otherwise.
	 *
	 * */
	bool isSubtEmpty(Set* s);

	/* An printer to this object */
	void print();
};

#endif /* SRC_TOOLS_SET_H_ */
