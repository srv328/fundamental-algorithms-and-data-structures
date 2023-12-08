# Graph Class

The `Graph` class manages operations on a graph, including adding/removing vertices and edges, traversal algorithms, and file I/O for graph data.

## How to Use

### Initializing a Graph
Graph graph(5); // Create a graph with 5 vertices

### Loading Graph from file
graph.loadFromFile("graph.txt"); // Load graph data from a file

## Functions

- `addVertex()`: Adds a new vertex to the graph.
- `removeVertex(vertex)`: Removes a specific vertex from the graph.
- `addEdge(from, to)`: Adds an edge between vertices 'from' and 'to'.
- `removeEdge(from, to)`: Removes an edge between vertices 'from' and 'to'.
- `print()`: Displays the adjacency matrix representing the graph.
- `depthFirstTraversal()`: Performs a depth-first traversal of the graph.
- `findConnectedComponents()`: Finds all connected components in the graph.
- `saveToFile(filename)`: Saves the graph to a file.
- `loadFromFile(filename)`: Loads the graph from a file.

### Operations

*   Adding a vertex: `graph.addVertex();`
*   Removing an edge: `graph.removeEdge(4, 1);`
*   Adding an edge: `graph.addEdge(1, 1);`

### Graph Traversal

*   Depth-first traversal: `graph.depthFirstTraversal();`

### Connected Components

*   Finding connected components: `graph.findConnectedComponents();`

### Saving Graph to File

Uncomment the following line to save changes to a file:
	// graph.saveToFile("graph.txt");