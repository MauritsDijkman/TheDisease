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

struct NodeAndPriority {
	int node;
	float priority;

	NodeAndPriority(int node_, float priority_) { node = node_; priority = priority_; }
	int GetNode() { return node; }
};

// create struct with one operation, for use in the comparisons needed by the priority queue
   // (might be better to have in a separate file and included?)
struct ComparePriority
{
	bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs)
	{
		// make it a min queue
		return lhs.priority > rhs.priority;
	}
};

float Graph::GetHeuristic(Vec3 a, Vec3 b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<int> Graph::Dijkstra(int startNode, int goalNode)
{
	// Declare helper variables
	float new_cost = 0;
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

	for (int i = 0; i < cost_so_far.size(); i++)
		cost_so_far[i] = 0.0f;

	bool hasReachedEndNode = false;

	while (!frontier.empty())
	{
		current = frontier.top().node;
		frontier.pop();

		if (current == goalNode) {
			cout << "Same node! || " << current << " || " << goalNode << endl;
			hasReachedEndNode = true;
			break;
		}

		for (Node next : GetNeighbours(current))
		{
			cout << "Current: " << current << " || Neighbour: " << next.GetLabel() << endl;

			new_cost = cost_so_far[current] + cost[current][next.GetLabel()];
			//if (count(cost_so_far.begin(), cost_so_far.end(), next.GetLabel()) || new_cost < cost_so_far[next.GetLabel()])
			if (cost_so_far[next.GetLabel()] == 0.0f || new_cost < cost_so_far[next.GetLabel()])
			{
				cost_so_far[next.GetLabel()] = new_cost;
				//currentNodeAndPriority->priority = new_cost;
				currentNodeAndPriority->priority = new_cost + GetHeuristic(node[goalNode]->GetPos(), next.GetPos());
				currentNodeAndPriority->node = next.GetLabel();
				frontier.push(*currentNodeAndPriority);
				came_from[next.GetLabel()] = current;
			}
		}
	}

	if (hasReachedEndNode)
	{
		vector<int> path;

		while (current != startNode)
		{
			path.push_back(current);
			current = came_from[current];
		}

		path.push_back(startNode);

		cout << "Has reached end node!" << endl;
		reverse(path.begin(), path.end());
		return path;
	}
}
