#include "Graph.h"
#include <iostream>
using namespace std;

Graph::Graph(int n){
	//if the graph to be created is smaller then one then we throw an out of range
	if (n < 1){
		throw out_of_range("Graph is too small");
	}
	//create the new array of AdjListNode and set them to NULL
	//will add the values in at the addEdge
	//the index will not be stored in the nodes.
	//Only neighbor indexes will be stored in the nodes
	this->m_size = n;
	
	m_adjLists = new AdjListNode*[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_adjLists[i] = NULL; //setting each first node to NULL
		

	}
		
}

Graph::AdjListNode::AdjListNode(int v, AdjListNode *ptr)
{
	m_vertex = v;//set the vertex to the neighbor vertex value
	ptr = NULL;
}
void Graph::addEdge(int u, int v)
{
	if ((u < 0 || u >= m_size) || (v < 0 || v >= m_size))
	{
		throw out_of_range("out of bounds");
	}

	AdjListNode *X = new AdjListNode(v); //Creating a dummy node to add at the beginning
	//each m_vertex will equal the edge node
	
	if (m_adjLists[u] != NULL) //If the index is null then I am adding the dummy node in the null space
		X->next = m_adjLists[u]; //set the dummy nodes next to equal the current node
	m_adjLists[u] = X;

	AdjListNode *P = new AdjListNode(u);

	if (m_adjLists[v] != NULL)
		P->next = m_adjLists[v];
	m_adjLists[v] = P;

	
	
}

void Graph::dump(){
	AdjListNode* n;//traverse the list with a dummy node
	for (int i = 0; i < m_size; i++){
		n = m_adjLists[i];
		cout << "[ " << i << "]: ";//this prints out the current index of the array

		while (n != NULL)
		{
			cout << " " << n->m_vertex;//Traversing the list through until a null is reached

			n = n->next;
		}
		
		cout << endl;
	}
}

Graph::Graph(const Graph& G){
	m_size = G.m_size;
	if (G.m_adjLists != NULL)		
	{
		m_adjLists = new AdjListNode*[m_size];//create an empty graph of NULL
		for (int i = 0; i < m_size; i++)
		{
			m_adjLists[i] = NULL;


		}
		//create m_adjLists with the contents G.m_adjLists
		//Using loops we add the new values like we would with an add edge.
		AdjListNode *X;
		
		for (int i = 0; i < m_size; i++)
		{
			while (G.m_adjLists[i] != NULL)
			{
				//system("pause");
				X = new AdjListNode(G.m_adjLists[i]->m_vertex);
				
				if (m_adjLists[i] != NULL) //If the index is null then I am adding the dummy node in the null space
					X->next = m_adjLists[i]; //set the dummy nodes next to equal the current node
				m_adjLists[i] = X;

				G.m_adjLists[i] = G.m_adjLists[i]->next;	
				
			}
		}
	}
	else{
		m_adjLists = NULL;
	}
		
}

const Graph& Graph::operator= (const Graph& rhs){
	AdjListNode *n;
	AdjListNode *k;
	//this->~Graph();

	//we want to delete the list here
	for (int i = 0; i < m_size; i++)
	{
		n = m_adjLists[i];
		k = n;
		while (n != NULL)
		{
			k = k->next;
			delete n;
			n = k;
		}
	}
	delete[]m_adjLists;

	//Then want to create a new list of the size of the new rhs
	m_size = rhs.m_size;
	m_adjLists = new AdjListNode*[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_adjLists[i] = NULL;


	}
	AdjListNode *X;
	AdjListNode *p;
	for (int i = 0; i < m_size; i++)
	{
		X = rhs.m_adjLists[i];
		
		while (X != NULL)
		{
			//system("pause");
			p = new AdjListNode(X->m_vertex);

			if (m_adjLists[i] != NULL) //If the index is null then I am adding the dummy node in the null space
				p->next = m_adjLists[i]; //set the dummy nodes next to equal the current node
			m_adjLists[i] = p;

			X = X->next;
			

		}
	}
	return *this;
}
int Graph::size(){
	return m_size;
}
Graph::~Graph(){
	//use 2 pointers to traverse each list and delete it
	//the k will equal the next node and n will delete the node previous
	AdjListNode *n;
	AdjListNode *k;
	
	for (int i = 0; i < m_size; i++)
	{
		n = m_adjLists[i];
		k = n;
		while (n!=NULL)
		{
			k = k->next;
			delete n;
			n = k;
		}
	}
	delete[] m_adjLists;
	
}
Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd){
	//m_Gptr = Gptr;
	m_source = v;
	if (v != -1){ //If the default constructor is called then it will pass over the statement
		if (isEnd == false){ //if its the beggining then I want m_where to equal  
							//the beginning of the linked list in the current index
			m_source = v;
			m_Gptr = Gptr;
			
			
			m_where = Gptr->m_adjLists[m_source];
			

		}

		if (isEnd == true){
			//if its the end then I want m_where to equal NULL to stop the iteration when NULL is reached

			m_where = NULL;
			m_Gptr = Gptr;
			m_source = v;
			
		}
	}
	
}
Graph::NbIterator Graph::nbBegin(int v){
	
	
	return Graph::NbIterator(this, v, false);//send the default contructor the graph and the index

}
Graph::NbIterator Graph::nbEnd(int v){
	return Graph::NbIterator(this, v, true);//send the default contructor the graph and the index
}
int Graph::NbIterator::operator*() {
	if (m_where == NULL) {
		throw out_of_range("NbIterator dereference error.");
	}

	return m_where->m_vertex;
}

bool Graph::NbIterator::operator!=(const NbIterator& rhs){

	return (m_where != rhs.m_where);//If m_where is NULL then it will cause the for loop in driver to end
	
}
void Graph::NbIterator::operator++(int dummy){
	//if the first node in the list is null then it will throw an out of range exception
	if (m_where == NULL) {
		throw out_of_range("NULL");
	}
	
		m_where = m_where->next;	//Increase m_where to the next. This should stop when m_where is NULL
	
	

}
Graph::EgIterator::EgIterator(Graph *Gptr, bool isEnd)
{
	
	m_Gptr = Gptr;
	
	
	if (m_Gptr != NULL){//If the default constructor is called then I want to pass over
		if (isEnd == false)
		{
			//I want to start at the beginning of the first index of the first node
			m_source = 0;
			m_where = m_Gptr->m_adjLists[m_source];
			

		}
		if (isEnd == true)
		{
			m_source = Gptr->m_size;
			m_where = NULL;
			//We want to stop when have reached both a NULL and the last Index
		}
		
	}
}
Graph::EgIterator Graph::egBegin()
{
	return Graph::EgIterator(this, false);//this sends the graph and the false value to show its the beginning 
}

Graph::EgIterator Graph::egEnd()
{
	return Graph::EgIterator(this, true);//this sends the graph and the true value to show its the end

}

void Graph::EgIterator:: operator++(int dummy){
	//I want to traverse each list and each time the list reaches a null we go to the next list
	//m_source is used to tell which index in the array we are at
	//
	m_where = m_where->next;
	//were finding the first non NULL value here
	while (m_where == NULL)
	{
		m_source++;
		if (m_Gptr->m_size <= m_source){
			return; //return if we have reached the end a NULL and the last index
		}
		m_where = m_Gptr->m_adjLists[m_source]; //This is setting us to the next index of the array
	}
	//m_source>m_where->vertex is what allows to not duplicate edges.
	//It will cause the smaller vertices to print their edges first
	while (m_source > m_where->m_vertex && m_where != NULL){
	m_where = m_where->next;

		while (m_where == NULL)//If m_where reaches the NULL it goes to the next list again
		{
			m_source++;
			if (m_Gptr->m_size<=m_source){
				return;//return if we have reached the NULL and the last index
			}
			m_where = m_Gptr->m_adjLists[m_source];//This is setting us to the next index of the array
		}
	}
	
}
std::pair<int, int> Graph::EgIterator::operator*() 
{

	if (m_where == NULL) {
		throw out_of_range("EgIterator dereference error.");
	}

	return std::pair<int, int>(m_source, m_where->m_vertex);
}
bool Graph::EgIterator::operator!=(const EgIterator& rhs){
	//if m_where has reached the NULL and the source has reached the end of the array size
	return (m_where != rhs.m_where&&m_source!=rhs.m_Gptr->m_size);
}