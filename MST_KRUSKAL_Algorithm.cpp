#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> Ipear;
struct Graph {
	int V, E;// V-Vertices, E_Edges
	vector<pair<int, Ipear>> edges;
	Graph(int V, int E) {
		this->V = V;
		this->E = E;
	}

	void AddEdge(int u, int v, int w) {
		edges.push_back({ w,{u,v} });
	}

	int MST_Kruskal();
};

//To represent Disjoint Sets
struct DisjointSets {
	int* parent, * rank;
	int n;
	//constructor
	DisjointSets(int n) {
		//Allocate memory
		this->n = n;
		parent = new int[n];
		rank = new int[n];
		//Initially, all the vertices are in different sets and have rank equal to 0
		for (int i{}; i < n; i++) {
			rank[i] = 0;
			parent[i] = i; //every element is parent of itself
		}
	}

	//Find the parent of a Node "u" path Compression
	int find(int u) {
		//we are finding the root head 
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	//Union by Rank
	void Union(int x, int y) {
		//find the root heads of x and y
		x = find(x);
		y = find(y);
		//Make tree with smaller height subtree of the other tree
		if (rank[x] > rank[y])
			parent[y] = x;
		else if (rank[x] < rank[y])
			parent[x] = y;
		else {
			parent[x] = y;
			rank[y]++;
		}
	}
};

int Graph::MST_Kruskal() {
	int mst_w{}; //initialize result
	//sorting edges by their weights
	sort(edges.begin(), edges.end());
	//Disjoint all the sets
	DisjointSets disjoint(V);

	vector<pair<int, Ipear>>::iterator it;
	for (auto it = edges.begin(); it != edges.end(); it++) {
		int u = it->second.first;
		int v = it->second.second;

		int set_u = disjoint.find(u);
		int set_v = disjoint.find(v);

		if (set_u != set_v) {
			cout << u << "-" << v << endl;
			mst_w += it->first;
			disjoint.Union(set_u,set_v);
		}
		
	}
	return mst_w;
}

int main()
{
	int V = 10, E = 15;
	Graph g(V, E);
	g.AddEdge(1,2,1);
	g.AddEdge(2,3,1);
	g.AddEdge(4,2,1);
	g.AddEdge(5,6,1);
	g.AddEdge(6,7,2);
	g.AddEdge(8,9,2);
	g.AddEdge(5,9,3);
	g.AddEdge(5,3,3);
	g.AddEdge(1,3,4);
	g.AddEdge(6,4,4);
	g.AddEdge(9,4,5);
	g.AddEdge(5,7,6);
	g.AddEdge(8,5,7);
	g.AddEdge(6,1,7);
	g.AddEdge(9,7,8);
	cout << "edges of the MST are:\n";
	int w = g.MST_Kruskal();
	cout << "MST weight is: " << w << endl;
}