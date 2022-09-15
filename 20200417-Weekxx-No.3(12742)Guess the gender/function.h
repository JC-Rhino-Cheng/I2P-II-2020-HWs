#ifndef FUNCTION_H
#define FUNCTION_H

class Vertex {
	friend class Graph;
	private:
		int index;
		Vertex *nextVertex;
	public:
		Vertex(int index = 0) {
			this->index = index;
			this->nextVertex = nullptr;
	}
};

/*
 * There are 2 ways to save the graph in data structure in general, shown as the following: 
 * 1. Adjacency Matrix
 *   Use a 2D array named "G". If (i, j) connects with each other, set G[i][j] to be true.
 * 2. Adjancency List
 *   Use N�� lists, with N representing the number of leading nodes.
 *   G[i] is the ith list and the node in G[i] represents the neighbors of node i.
 * Here we are using the second method (Adjancency List), since there are too many edges.
 */
class Graph {
	private:
		int numberOfVertices;
		Vertex **adjacencyList;
		int *vertexInfo;// VertexInfo�N��: �u��Vertex�v���ʧO�A1�N��k�A0�N��k�A-1�N��|���[���
	public:
		Graph() {}// Default constructor�A���|�Ψ�A�ҥH���ޥ�
		Graph(int n);

		// TODO: Implement function to add edge from srouce to destination, you can insert Vertex destination at the front of the list of adjacencyList[source]
		void addEdge(int source, int destination);

		// TODO: Implement a depth first search on the graph to solve the problem
		bool dfs(int vertex);//�L����k����²��A�ڤ��Q�ΡC�ڥΧڦۤv��

		// TODO: Implement your solver function
		bool solver();

		~Graph();
};

#endif
