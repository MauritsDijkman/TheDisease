#include "Graph.h"

using namespace std;

Graph::Graph() {}

Graph::~Graph() {}

bool Graph::OnCreate(vector<Node*> nodes_)
{
	// ASSUMTION; nodes_ vector has the node with label "i" in the "i" position of the vector

	// Given a list of nodes
	// Initialize a matrix of costs with 0.0 weights

	int numNodes = nodes_.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		// Check if the current i is the same as in the list
		if (i != nodes_[i]->GetLabel())
			return false;

		// Add the nodes to internal list
		node[i] = nodes_[i];

		// Set up the connections
		cost[i].resize(numNodes);
		for (int j = 0; j < numNodes; j++)
		{
			// Initialize connections to other nodes
			cost[i][j] = 0.0f;
		}
	}

	return true;
}

int Graph::NumNodes()
{
	return node.size();
	// return cost.size();
}

void Graph::AddWeightConnection(int fromNode, int toNode, float weight)
{
	cost[fromNode][toNode] = weight;
}

vector<int> Graph::GetNeighbours(int fromNode)
{
	vector<int> result = {};

	for (int j = 0; j < NumNodes(); j++)
	{
		if (cost[fromNode][j] > 0.0f)
			result.push_back(j);
	}

	return result;
}

vector<int> Graph::Dijkstra(int startNode, int goalNode)
{
	/**
	// Declare helper variables
	float new_cost;
	int current;

	// Declare current NodeAndPriority
	NodeAndPriority* currentNodeAndPriority;
	currentNodeAndPriority = new NodeAndPriority(startNode, 0.0f);

	// Set up prority queue for frontier of nodes
	priority_queue< NodeAndPriority, deque<NodeAndPriority>, ComparePriority> frontier;
	frontier.push(*currentNodeAndPriority);

	// Track solution path
	vector<int> came_from;
	came_from.resize(NumNodes());

	// Store cost so far to reach that node
	map<int, float> cost_so_far;
	cost_so_far[startNode] = 0.0f;

	// [TODO] Implement the algorithm

	// Start looping through the frontier, put it in "current"
	{
		// Get the node from the top of the frontier
		// Pop it off
		// If it's the goal, then break out of the loop

		// For the neighbours of current node
		{
			// Calculate new_cost
			// If neighbour is not in cost_so_far OR new_cost is lower
			{
				// Found a better path. so update structure (look at pseudocode algorithm)
			}
		}
	}

	frontier = priority_queue;

	while (!frontier.empty())
	{
		current = frontier.get();

		if (current == goal)
			break;

		for (Node next in graph.neighbours)
		{
			new_cost = cost_so_far[current] + graph.cost(current, node);

		}
	}

	return came_from;
	/**/

	vector<int> Test;
	return Test;
}
