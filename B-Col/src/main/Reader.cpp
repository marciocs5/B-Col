/*
 * Reader.cpp
 *
 *  Created on: 19 de dez de 2016
 *      Author: marcio
 */

#include "Reader.h"



Reader::Reader(){}

Reader::~Reader(){}

Graph* Reader::read(std::istream& dimacs){
	
    int n;
	string temp;

    Graph * myGraph = new Graph(n);

    std::string line;
    while (getline(dimacs, line))
    {
        std::istringstream iss(line);
        char ch;
        if (iss >> ch)
        {
            size_t from, to;
            std::string format;

            switch(ch) {
                case 'c': break;
                case 'p': 
			{  
			iss >> temp >> n >> to ;
                        myGraph = new Graph(n);
			}
			break;
                case 'e':                     
                	{
                		iss >> from >> to;
                		myGraph->addEdge(from-1, to-1);
                	}
                   break;
                default: 
                    return NULL;
            }
        }
    }
    return myGraph;
}


