#include <iostream>
#include <stack>
#include <vector>
using namespace std;

// Data structure to store Graph1 edges
struct Edge {
	int src, dest;
};

// Class to represent a Graph1 object
class Graph1
{
public:
	// construct a vector of vectors to represent an adjacency list
	vector<vector<int>> adjList;

	// stores indegree of a vertex
	vector<int> indegree;

	// Graph1 Constructor
	Graph1(vector<Edge> const& edges, int N)
	{
		// resize the vector to N elements of type vector<int>
		adjList.resize(N);

		// initialize indegree
		vector<int> temp(N, 0);
		indegree = temp;

		// add edges to the directed Graph1
		for (auto& edge : edges)
		{
			// add an edge from source to destination
			adjList[edge.src].push_back(edge.dest);

			// increment in-degree of destination vertex by 1
			indegree[edge.dest]++;
		}
	}
};

// performs Topological Sort on a given DAG
bool doTopologicalSort(Graph1 const& Graph1, vector<int>& L, int N)
{
	vector<int> indegree = Graph1.indegree;

	// Set of all nodes with no incoming edges
	vector<int> S;
	for (int i = 0; i < N; i++) {
		if (!indegree[i]) {
			S.push_back(i);
		}
	}

	while (!S.empty())
	{
		// remove a node n from S
		int n = S.back();
		S.pop_back();

		// add n to tail of L
		L.push_back(n);

		for (int m : Graph1.adjList[n])
		{
			// remove edge from n to m from the Graph1
			indegree[m] -= 1;

			// if m has no other incoming edges then
			// insert m into S
			if (!indegree[m]) {
				S.push_back(m);
			}
		}
	}

	// if Graph1 has edges then Graph1 has at least one cycle
	for (int i = 0; i < N; i++) {
		if (indegree[i]) {
			return false;
		}
	}

	return true;
}



// Abstraction of a graph

class Graph
{
private:
	int n;							// Number of vertices
	int** adj;						// Adjacency matrix
public:
	Graph(int size);				// Constructor
	~Graph();						// Destructor
	void addEdge(int x, int y); 	// Add an edge the the graph
	bool isConnected(int x, int y);	// Check if two vertices are connected
	void DFS(int start, int end);	// Depth first search
};


// Constructor

Graph::Graph(int size)
{
	if (size < 2)				// The graph must have at least 2 vertices
	{
		n = 2;
	}
	else
	{
		n = size;
	}

	adj = new int* [n];			// Allocate memory for adjacency matrix

	for (int i = 0; i < n; ++i)
	{
		adj[i] = new int[n];	// Allocate memory for adjacency matrix
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			adj[i][j] = 0;		// Initialize the vertices to 0
		}
	}
}

// Destructor
Graph::~Graph()
{
	for (int i = 0; i < n; ++i)
	{
		delete[] adj[i];
	}
	delete[] adj;
}


// Add an edge to the graph

void Graph::addEdge(int x, int y)
{
	adj[x - 1][y - 1] = adj[y - 1][x - 1] = 1;
}


// Check if two vertices are connected

bool Graph::isConnected(int x, int y)
{
	return (adj[x - 1][y - 1] == 1);
}


// Depth first search

void Graph::DFS(int start, int end)
{
	stack <int> s;									// Create a stack of ints
	bool* visited = new bool[n + 1];					// Boolean array to represent which vertices we've visited

	for (int i = 0; i <= n; ++i)							// Initialize all elements of visited to false
	{
		visited[i] = false;
	}

	s.push(start);									// Push the vertex onto the stack
	visited[start] = true;							// Mark this node as visited

	if (start == end)								// End the function if we're at our destination
	{
		return;
	}

	cout << "Depth-first search starting from point: " << start << endl;

	while (!s.empty())								// While the stack is not empty
	{
		int k = s.top();							// Save the top element before popping it off
		s.pop();

		if (k == end)								// Break out of the loop if we've reached our destination
		{
			break;
		}

		cout << k << " ";

		for (int i = n; i >= 0; --i)						// For all adjacent vertices
		{
			if (isConnected(k, i) && !visited[i])	// If they're connected and we haven't visited it yet
			{
				s.push(i);							// Add it to our stack, and mark that we've visited it
				visited[i] = true;
			}
		}
	}
	cout << end << endl;
	delete[] visited;								// De-allocate the visited array
}


// Main function



int funk1()
{
	Graph g(8);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(2, 4);
	g.addEdge(2, 5);
	g.addEdge(2, 6);
	g.addEdge(3, 7);
	g.addEdge(7, 8);
	g.DFS(3, 7);	// starting search 
	return 0;
}

int funk2()
{
	// vector of Graph1 edges as per above diagram
	vector<Edge> edges =
	{
		{ 0, 6 }, { 1, 2 }, { 1, 4 }, { 1, 6 }, { 3, 0 }, { 3, 4 },
		{ 5, 1 }, { 7, 0 }, { 7, 1 }
	};

	// Number of nodes in the Graph1
	int N = 8;

	// create a Graph1 from edges
	Graph1 Graph1(edges, N);

	// Empty list that will contain the sorted elements
	vector<int> L;

	// Perform Topological Sort
	if (doTopologicalSort(Graph1, L, N))
	{
		// print topological order
		for (int i : L)
			cout << i << " ";
	}
	else {
		cout << "Graph1 has at least one cycle. "
			"Topological sorting is not possible";
	}

	return 0;
}


int main()
{
	 funk1();
	 funk2();
	return 0;
}
