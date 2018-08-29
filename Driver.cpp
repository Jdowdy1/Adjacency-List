// File: test1.cpp
//
// CMSC 341 Spring 2017
// Project 1 
//
// Basic testing of Graph class
//

#include <iostream>

// need this for pair template
//
#include <utility>
using namespace std;

#include "Graph.h"

int main() {

	Graph G(50);

	// add some edges
	G.addEdge(3, 4);
	G.addEdge(1, 4);
	G.addEdge(0, 3);
	G.addEdge(0, 4);
	G.addEdge(0, 1);
	G.addEdge(1, 2);
	G.addEdge(2, 4);
	G.addEdge(20, 4);
	G.addEdge(2, 30);
	G.addEdge(23, 45);
	G.addEdge(12, 4);
	G.addEdge(15, 7);
	G.addEdge(2, 9);
	G.addEdge(8, 49);
	G.addEdge(6, 49);
	G.addEdge(37, 19);
	G.addEdge(41, 13);
	G.addEdge(6, 47);
	G.addEdge(25, 49);
	cout << "DUMPING THE LIST:";
	cout << endl;
	// dump out data structure
	G.dump();
	cout << endl;

	
	// Test neighbor iterator
	//
	Graph::NbIterator nit;
	cout << endl;
	cout << "\nThe neighbors of vertex 4 are:\n";
	for (nit = G.nbBegin(4); nit != G.nbEnd(4); nit++) {
	cout << *nit << " ";
	}
	cout << endl;
	cout << endl;
	cout << "\nThe neighbors of vertex 49 are:\n";
	for (nit = G.nbBegin(49); nit != G.nbEnd(49); nit++) {
		cout << *nit << " ";
	}
	cout << endl;
	cout << endl;
	// Test edge iterator
	//
	Graph::EgIterator eit;
	pair<int, int> edge;

	cout << "\nThe edges in the graph are:\n";
	for (eit = G.egBegin(); eit != G.egEnd(); eit++) {

	edge = *eit;   // get current edge

	// the two data members of a pair are first and second
	//
	cout << "(" << edge.first << ", " << edge.second << ") ";

	}
	cout << endl;

	cout << endl;
	cout << endl;

// Testing of Graph destructor, copy constructor and assignment operator

	Graph* Gptr = new Graph(5);

	// add some edges
	Gptr->addEdge(3, 4);
	Gptr->addEdge(1, 4);
	Gptr->addEdge(0, 3);
	Gptr->addEdge(0, 4);
	Gptr->addEdge(0, 1);
	Gptr->addEdge(1, 2);
	Gptr->addEdge(2, 4);
	cout << "Dumping the original adjacency list before testing the copy constructor" << endl << endl;
	// dump out data structure
	Gptr->dump();
	// make a copy using copy constructor
	Graph* Gptr2 = new Graph(*Gptr);
	cout << endl << endl << "Dumping the copied adjacency list" << endl;
	Gptr2->dump();
	cout << endl;
	// get rid off original graph
	// check if new graph is still there
	delete Gptr;
	
	cout << "Dumping the copied list after deleting the orginal" << endl << endl;
	Gptr2->dump();

	// Make another graph and dump
	Graph G3(3);
	G3.addEdge(0, 1);
	G3.addEdge(0, 2);
	G3.addEdge(1, 2);

	cout << endl;
	cout << "Dumping a newly created adjacency list to test the assignment operator" << endl;
	G3.dump();
	
	// Copy over G3 and dump
	G3 = *Gptr2;
	cout << "Dumping the same list after the assigning Gptr2" << endl;
	G3.dump();
	delete Gptr2;

	cout << endl;
	cout << "Dumping G3 again after deleting Gptr2" << endl;
	G3.dump();
	
}