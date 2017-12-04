/*
 * Reader.h
 *
 *  Created on: 19 de dez de 2016
 *      Author: marcio
 */

#ifndef SRC_MAIN_READER_H_
#define SRC_MAIN_READER_H_

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <istream>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../tools/Graph.h"

using namespace std;

class Reader {
public:
	Reader();

	virtual ~Reader();

    Graph * read(std::istream& dimacs);
};

#endif /* SRC_MAIN_READER_H_ */
