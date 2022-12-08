#ifndef GRAPH_H
#define GRAPH_H
#include "Node.h"
#include <vector>// From STL
#include <map>
#include <queue>

using namespace std;

class Graph{
private:
// List of the nodes
map<int, Node*> node; // Could use STL vector, but map matches some textbooks
vector<vector<float>> cost;// 2D matrix of the connection costs
public:
Graph();
~Graph();
bool OnCreate(vector<Node*> nodes_);
int NumNodes();
Node* GetNode(int label) { return node[label]; }
void AddWeightConnection(int fromNode, int toNode, float weight);
vector<int> GetNeighbours(int fromNode);
vector<int> Dijkstra(int startNode, int goalNode);
vector<int> AStar(int startNode, int goalNode);
float GetHeuristic(Vec3 a, Vec3 b);
};
#endif // !GRAPH_H