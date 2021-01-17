#include <vector>
#include <set>
#include <stack>
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;


class Graph
{
	int V;
	vector<int> *adj;//just a vector instead?

	void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[]);

public:
	Graph(int V);
	void addEdge(int v, int w);
	void SCC(); //prints all SCCs

};

Graph::Graph(int V)
{
	this->V = V;
	adj = vector<int> [V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w):
}


//enter implementation baby
// void Graph::Ta(Graph G)
// {
// 	int* time;
// 	//static int time = 0; //what does static do and how I can just use a pointer?
// 	index = 0;
// 	vector<int> S;
// 	for ()

// 	disc[u] = low[u];
// 	st->push;
// 	stackMember


// }


algorithm tarjan is
 input: graph G = (V, E) so V = allUsers and E = following relationships
 output: set of strongly connected components (sets of vertices)

index = 0;
vector<int> S;


//setting them all to undiscovered
for(map<string,User*>::iterator it1 = allUsers.begin(); it1 != allUsers.end(); it1++)
{
	//if(i == undefined) //? how to check??
	it1->index = -1;
}

for(map<string,User*>::iterator it1 = allUsers.begin(); it1 != allUsers.end(); it1++)
{
	//if(i == undefined) //? how to check??
	if(it1->index == -1)
	{
		strongconnect(v);
	}
}



	




function strongconnect(User* v)
// Set the depth index for v to the smallest unused index
{
	v.index = index;
	v.lowlink = index;
	index = index + 1;
	S.push(v);
	v.onStack = true;

	// Consider successors of v
	for (each (v, w) in E )
	{
	  if (w.index is undefined)
	  {
	    // Successor w has not yet been visited; recurse on it
	    strongconnect(w)
	    v.lowlink  := min(v.lowlink, w.lowlink)
	  }
	  else if (w.onStack)
	  {
	    // Successor w is in stack S and hence in the current SCC
	    // If w is not on stack, then (v, w) is a cross-edge in the DFS tree and must be ignored
	    // Note: The next line may look odd - but is correct.
	    // It says w.index not w.lowlink; that is deliberate and from the original paper
	    v.lowlink  = min(v.lowlink, w.index);
	  }
	}

	// If v is a root node, pop the stack and generate an SCC
	if (v.lowlink = v.index) 
	{
	  	start a new strongly connected component
	  	repeat
	    w = S.pop();
	    w.onStack = false;
	    add w to current strongly connected component
	  while (w != v)
	  {
	  output the current strongly connected component
	  }
	}
		
}


set<User*> myset;
stack<User*> mystack;
vector<Node*> myvec;

Nodes are user*,timevisited,lowlink;



















