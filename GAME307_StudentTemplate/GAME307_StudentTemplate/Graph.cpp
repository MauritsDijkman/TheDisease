#include "Graph.h"
using namespace std;

Graph::Graph() {}
Graph::~Graph() {}

bool Graph::OnCreate(vector<Node*> nodes_){
	// ASSUMTION; nodes_ vector has the node with label "i" in the "i" position of the vector
	// Given a list of nodes
	// Initialize a matrix of costs with 0.0 weights
	int numNodes = nodes_.size();
	cost.resize(numNodes);
	for (int i = 0; i < numNodes; i++){
		// Check if the current i is the same as in the list
		if (i != nodes_[i]->GetLabel())
			return false;
		// Add the nodes to internal list
		node[i] = nodes_[i];
		// Set up the connections
		cost[i].resize(numNodes);
		// Initialize connections to other nodes
		for (int j = 0; j < numNodes; j++)
			cost[i][j] = 0.0f;
	}
	return true;
}
int Graph::NumNodes(){
	// Can return both
	return node.size();
	// return cost.size();
}
void Graph::AddWeightConnection(int fromNode, int toNode, float weight) {
	// Set the cost of the nodes to the given weight
	cost[fromNode][toNode] = weight;
}
vector<int> Graph::GetNeighbours(int fromNode){
	// Return the vector int list with all the neigbours
	vector<int> result = {};
	for (int j = 0; j < NumNodes(); j++){
		if (cost[fromNode][j] > 0.0f)
			result.push_back(j);
	}
	return result;
}

struct NodeAndPriority {
	// Class to store the node priority information
	int node;
	float priority;
	NodeAndPriority(int node_, float priority_) { node = node_; priority = priority_; }
	int GetNode() { return node; }
};

// Create struct with one operation, for use in the comparisons needed by the priority queue
   // (might be better to have in a separate file and included?)
struct ComparePriority{
	bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs){
		// Make it a min queue
		return lhs.priority > rhs.priority;
	}
};

float Graph::GetHeuristic(Vec3 a, Vec3 b){
	// Return the distance between two positions
	return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<int> Graph::Dijkstra(int startNode, int goalNode){
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
	// Set every cost so far value to 0.0f 
	// This will be used for checking if value is already in the list later
	for (int i = 0; i < cost_so_far.size(); i++)
		cost_so_far[i] = 0.0f;
	// Usage for returning value
	bool hasReachedEndNode = false;
	while (!frontier.empty()){
		// Set the current node to the top one of the list and remove 
		current = frontier.top().node;
		frontier.pop();
		// Check if the current node is the goal node
		if (current == goalNode){
			// Debug to check if the current node is the goal node
			cout << "Same node! || " << current << " || " << goalNode << endl;
			hasReachedEndNode = true;
			break;
		}
		// Run code for every neighbour
		for (Node next : GetNeighbours(current)){
			// Debug to check which neighbours the current node has
			cout << "Current: " << current << " || Neighbour: " << next.GetLabel() << endl;
			// Set the cost so far to the already existing cost
			new_cost = cost_so_far[current] + cost[current][next.GetLabel()];
			// Check if the node is already in the list or if it's smaller than the cost so far
			if (cost_so_far[next.GetLabel()] == 0.0f || new_cost < cost_so_far[next.GetLabel()]){
				cost_so_far[next.GetLabel()] = new_cost;		// Set the cost so far for this node
				currentNodeAndPriority->priority = new_cost;	// Set the current priority
				currentNodeAndPriority->node = next.GetLabel();	// Set the current node
				frontier.push(*currentNodeAndPriority);			// Add the node and priority to the list
				came_from[next.GetLabel()] = current;			// Add the current node to the came from list
			}
		}
	}
	// Only return list when the end node has been reached
	if (hasReachedEndNode){
		// Create a vector int list for the path
		vector<int> path;
		// Keep getting the previous node while the start node has not been reached
		while (current != startNode){
			path.push_back(current);
			current = came_from[current];
		}
		// Add the start node to the list
		path.push_back(startNode);
		// Debug to check if the code has reached the end node
		cout << "Has reached end node!" << endl;
		// Reverse the list to start with the startNode
		reverse(path.begin(), path.end());
		return path;
	}
}

vector<int> Graph::AStar(int startNode, int goalNode){
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
	// Set every cost so far value to 0.0f 
	// This will be used for checking if value is already in the list later
	for (int i = 0; i < cost_so_far.size(); i++)
		cost_so_far[i] = 0.0f;
	// Usage for returning value
	bool hasReachedEndNode = false;
	while (!frontier.empty()){
		// Set the current node to the top one of the list and remove 
		current = frontier.top().node;
		frontier.pop();
		// Check if the current node is the goal node
		if (current == goalNode){
			// Debug to check if the current node is the goal node
			cout << "Same node! || " << current << " || " << goalNode << endl;
			hasReachedEndNode = true;
			break;
		}
		// Run code for every neighbour
		for (Node next : GetNeighbours(current)){
			// Debug to check which neighbours the current node has
			cout << "Current: " << current << " || Neighbour: " << next.GetLabel() << endl;
			// Set the cost so far to the already existing cost
			new_cost = cost_so_far[current] + cost[current][next.GetLabel()];
			// Check if the node is already in the list or if it's smaller than the cost so far
			if (cost_so_far[next.GetLabel()] == 0.0f || new_cost < cost_so_far[next.GetLabel()]){
				cost_so_far[next.GetLabel()] = new_cost;																// Set the cost so far for this node
				currentNodeAndPriority->priority = new_cost + GetHeuristic(node[goalNode]->GetPos(), next.GetPos());	// Set the current priority
				currentNodeAndPriority->node = next.GetLabel();															// Set the current node
				frontier.push(*currentNodeAndPriority);																	// Add the node and priority to the list
				came_from[next.GetLabel()] = current;																	// Add the current node to the came from list
			}
		}
	}
	// Only return list when the end node has been reached
	if (hasReachedEndNode){
		// Create a vector int list for the path
		vector<int> path;
		// Keep getting the previous node while the start node has not been reached
		while (current != startNode)
		{
			path.push_back(current);
			current = came_from[current];
		}
		// Add the start node to the list
		path.push_back(startNode);
		// Debug to check if the code has reached the end node
		cout << "Has reached end node!" << endl;
		// Reverse the list to start with the startNode
		reverse(path.begin(), path.end());
		return path;
	}
}