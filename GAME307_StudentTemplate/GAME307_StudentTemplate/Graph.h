#ifndef GRAPH_H
#define GRAPH_H

// Necessary includes
#include <vector>// From STL
#include <map>
#include <queue>

#include "Node.h"

// Namespace
using namespace std;

class Graph {
private:
	// List of the nodes
	map<int, Node*> node;		// Could use STL vector, but map matches some textbooks
	vector<vector<float>> cost;	// 2D matrix of the connection costs

public:
	// Constructor
	Graph();
	~Graph();

	bool OnCreate(vector<Node*> nodes_);

	// Return the number of nodes
	int NumNodes();

	// Get functions
	Node* GetNode(int label) { return node[label]; }
	vector<int> GetNeighbours(int fromNode);
	float GetHeuristic(Vec3 a, Vec3 b);

	// Add the weight value to each connection
	void AddWeightConnection(int fromNode, int toNode, float weight);

	// Algorithms
	vector<int> Dijkstra(int startNode, int goalNode);
	vector<int> AStar(int startNode, int goalNode);

	// Get closest node to the player
	int GetClosestNodeToPlayer(Vec3 playerPos);
};

#endif // !GRAPH_H
