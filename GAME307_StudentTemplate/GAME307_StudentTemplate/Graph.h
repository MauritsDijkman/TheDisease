#ifndef GRAPH_H
#define GRAPH_H

#include <vector>	// From STL
#include <map>
#include <queue>

#include "Node.h"

using namespace std;

class Graph
{
private:
	// List of the nodes
	// Could use STL vector, but map matches some textbooks
	map<int, Node*> node;

	// 2D matrix of the connection costs
	vector<vector<float>> cost;

private:
	//frontier = PriorityQueue;


public:
	Graph();
	~Graph();

	bool OnCreate(vector<Node*> nodes_);

	int NumNodes();
	Node* GetNode(int label) { return node[label]; }

	void AddWeightConnection(int fromNode, int toNode, float weight);
	vector<int> GetNeighbours(int fromNode);
	vector<int> Dijkstra(int startNode, int goalNode);
};

#endif
