#include <iostream>
#include <stack>
using namespace std;


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

int main()
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






/*

#include <iostream>
#include <algorithm>

using namespace std;

struct dane {
	bool odwiedzony;
	int poprzednik;
	int pre;
	int post;
	int id;
};

void odwiedzWezel(int** macierz, int n, dane* tab, int u, int& p) {
	tab[u].odwiedzony = true;
	tab[u].pre = p;
	p++;
	for (int i = 0; i < n; i++) {
		if (macierz[u][i] > 0 && !tab[i].odwiedzony) {
			tab[i].poprzednik = u;
			odwiedzWezel(macierz, n, tab, i, p);
		}
	}
	tab[u].post = p;
	p++;
}

dane* DFS(int** macierz, int n, int start) {
	dane* tab = new dane[n];
	for (int i = 0; i < n; i++) {
		tab[i].odwiedzony = false;
		tab[i].poprzednik = -1;
		tab[i].id = i;
	}
	int p = 1;
	odwiedzWezel(macierz, n, tab, start, p);
	for (int i = 0; i < n; i++)
		if (!tab[i].odwiedzony)
			odwiedzWezel(macierz, n, tab, i, p);
	return tab;
}

bool porownaj(dane a, dane b) {
	return a.post < b.post;
}

dane* sortowanieTopologiczne(int** macierz, int n) {
	dane* tab = DFS(macierz, n, 0);
	sort(tab, tab + n, porownaj);
	return tab;
}

int main() {
	int n;
	cout << "Ile wierzcholkow ma graf?\n n = ";
	cin >> n;
	cout << "Podaj macierz:" << endl;
	int** macierz = new int* [n];
	for (int i = 0; i < n; i++) {
		macierz[i] = new int[n];
		for (int j = 0; j < n; j++)
			cin >> macierz[i][j];
	}
	dane* tab = sortowanieTopologiczne(macierz, n);
	for (int i = 0; i < n; i++)
		cout << tab[i].id << " ";
	system("pause");
	return 0;
}

*/

/*
#include<iostream>
using namespace std;
int vertArr[20][20]; //the adjacency matrix initially 0
int count = 0;

void displayMatrix(int v) {
    int i, j;
    for (i = 0; i < v; i++) {
        for (j = 0; j < v; j++) {
            cout << vertArr[i][j] << " ";
        }
        cout << endl;
    }
}
void add_edge(int u, int v) {       //function to add edge into the matrix
    vertArr[u][v] = 1;
    vertArr[v][u] = 1;
}
int main(int argc, char* argv[]) 
{
    int v = 6;    //there are 6 vertices in the graph
    add_edge(0, 4);
    add_edge(0, 3);
    add_edge(1, 2);
    add_edge(1, 4);
    add_edge(1, 5);
    add_edge(2, 3);
    add_edge(2, 5);
    add_edge(5, 3);
    add_edge(5, 4);
    displayMatrix(v);

}
*/