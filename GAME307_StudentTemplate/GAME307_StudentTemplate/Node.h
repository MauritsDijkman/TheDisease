#ifndef NODE_H
#define NODE_H

#include "MMath.h"
#include <vector>

using namespace MATH;
using namespace std;

class Node {
private:
	void Galculate_H();

	int label;	// Label of the node

	float f;	// Distance amount (g + h)
	float g;	// Distance from start node to this node
	float h;	// Distance from this node to target node

	float distanceBetweenNodes;		// Distance between the provided node and this node

	vector<Node> connectedNodes;	// List with all the connectedNodes

	Node* targetNode;	// Target node (Node* test[4] also works)
	Node* previousNode;	// Node before this node (= new Node()

	Vec3 position;		// Position of the node

public:
	Node();
	~Node();

	// Get Functions
	float Get_F();
	float Get_G();
	Vec3 GetPos();
	Node* GetPreviousNode();
	vector<Node> GetConnections();

	// Set Functions
	void Set_DistanceBetweenNodes(Node* G_);
	void Set_F(float F_);
	void SetTargetNode(Node* targetNode_);
	void SetParent(Node parent_);
	void SetPosition(Vec3 position_);
};

#endif
