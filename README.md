# Kruskal's Algorithm (MST) in C++

A C++ implementation of Kruskal's algorithm, which builds a **Minimum Spanning Tree** (MST) for a weighted, undirected graph. It uses a **Disjoint Set Union (Union-Find)** data structure to detect cycles efficiently.

## What the Algorithm Does

A minimum spanning tree is a subset of the graph's edges that:

- connects all vertices,
- contains no cycles,
- has the smallest possible total weight.

## Algorithm Steps

1. Sort all edges by weight in ascending order.
2. Place each vertex in its own separate set.
3. Go through the edges one by one:
   - If the endpoints of the edge belong to **different** sets, add the edge to the MST and merge the two sets.
   - If they belong to the **same** set, skip the edge (adding it would create a cycle).
4. The result is the MST and its total weight.

## Code Structure

| Component | Description |
|---|---|
| `Graph` | Stores the number of vertices (`V`), the number of edges (`E`), and the list of edges as `(weight, (u, v))` |
| `Graph::AddEdge(u, v, w)` | Adds an edge between `u` and `v` with weight `w` |
| `Graph::MST_Kruskal()` | Runs Kruskal's algorithm, prints the MST edges, and returns the total weight |
| `DisjointSets` | Union-Find data structure |
| `find(u)` | Finds the root of `u` using **path compression** |
| `Union(x, y)` | Merges two sets using **union by rank** |

## Complexity

- **Time complexity:** `O(E log E)`, dominated by sorting the edges.
- **Space complexity:** `O(V + E)`.

Thanks to path compression and union by rank, `find` and `Union` run in nearly constant amortized time.

## Usage Example

```cpp
Graph g(10, 15);
g.AddEdge(1, 2, 1);
g.AddEdge(2, 3, 1);
// ... more edges
int w = g.MST_Kruskal();   // prints the MST edges and returns the total weight
```

## Sample Output

```
edges of the MST are:
1-2
2-3
4-2
5-6
6-7
8-9
5-3
5-9
MST weight is: 14
```

## Notes

- Vertex indices start at `0`. The example uses vertices `1` to `9`, so `V = 10` and vertex `0` is isolated.
- `DisjointSets` uses dynamic memory (`new[]`) without freeing it. Consider adding a destructor or replacing the arrays with `vector<int>` to avoid memory leaks.
- If the graph is not connected, the algorithm produces a **Minimum Spanning Forest** instead of a single tree.
