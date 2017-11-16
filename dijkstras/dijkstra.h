#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include <vector>

class Edge
{
public:
	Edge(int v1, int v2, int weight);
	int v1;
	int v2;
	unsigned int weight;
};

class Vertex
{
public:
	int n;
	bool visited;
	std::vector<Edge> linkedVertices;
};

class Graph
{
public:
	Graph(unsigned int N);
	~Graph();
	void addEdge(int v1, int v2, int weight);
	unsigned int *dijkstra();

private:
	unsigned int N;
	std::vector<int> visited;
	unsigned int *costs;
	Vertex *vertices;
};

Graph::Graph(unsigned int N):N(N)
{
	costs = new unsigned int[N + 1];
	vertices = new Vertex[N + 1];

	for (unsigned int i = 1; i <= N; i++)
	{
		costs[i] = 1000000;
		vertices[i].n = i;
		vertices[i].visited = false;
	}
}

Graph::~Graph()
{
	delete[] costs;
	delete[] vertices;
}

void Graph::addEdge(int v1, int v2, int weight)
{
	vertices[v1].linkedVertices.push_back(Edge(v1, v2, weight));
}

unsigned int* Graph::dijkstra()
{
	vertices[1].visited = true;
	costs[1] = 0;
	visited.push_back(1);

	unsigned int minWeight = -1;
	int newNode = -1;

	while (visited.size() < N)
	{
		minWeight = -1;
		newNode = -1;

		for (unsigned int i = 0; i < visited.size(); i++)
		{
			for (unsigned int j = 0; j < vertices[visited[i]].linkedVertices.size(); j++)
			{
				if (vertices[vertices[visited[i]].linkedVertices[j].v2].visited)
				{
					continue;
				}

				if (costs[visited[i]] + vertices[visited[i]].linkedVertices[j].weight < minWeight)
				{
					minWeight = costs[visited[i]] + vertices[visited[i]].linkedVertices[j].weight;
					newNode = vertices[visited[i]].linkedVertices[j].v2;
				}
			}
		}
		
		vertices[newNode].visited = true;
		costs[newNode] = minWeight;
		visited.push_back(newNode);
	}

	return costs;
}

Edge::Edge(int v1, int v2, int weight):v1(v1), v2(v2), weight(weight)
{

}

#endif /* __DIJKSTRA_H__ */
