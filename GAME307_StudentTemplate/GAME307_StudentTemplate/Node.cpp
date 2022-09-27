#include "Node.h"

Node::Node()
{
	previousNode = new Node();
	targetNode = new Node();
}

Node::~Node() {}

void Node::Galculate_H()
{
	Vec3 targetPos = targetNode->GetPos();

	float distanceX = targetPos.x - position.x;
	float distanceY = targetPos.y - position.y;

	// Distance = sqrt((x2-x2)^2 + (y2-y1)^2)
	h = sqrt((distanceY * distanceY) + (distanceX * distanceX));
}

#pragma region GetFunctions

float Node::Get_F()
{
	return f;
}

Vec3 Node::GetPos()
{
	return position;
}

Node* Node::GetPreviousNode()
{
	return previousNode;
}


float Node::Get_G()
{
	Node* previousNode_;
	previousNode_ = previousNode;

	//for (int i = 0; i < ) {
	while (previousNode_ != NULL)
	{
		g += previousNode_->Get_G();
		previousNode_ = previousNode_->GetPreviousNode();
	}

	return g;
}

vector<Node> Node::GetConnections()
{
	return connectedNodes;
}

#pragma endregion

#pragma region SetFunctions

void Node::Set_DistanceBetweenNodes(Node* G_)
{
	Vec3 targetPos = G_->GetPos();

	float distanceX = targetPos.x - position.x;
	float distanceY = targetPos.y - position.y;

	// Distance = sqrt((x2-x2)^2 + (y2-y1)^2)
	distanceBetweenNodes = sqrt((distanceY * distanceY) + (distanceX * distanceX));
}

void Node::Set_F(float F_)
{
	f = F_;
}

void Node::SetTargetNode(Node* targetNode_)
{
	targetNode = targetNode_;
	Galculate_H();
}

void Node::SetParent(Node parent_)
{
	// TODO: fix from Node to Node*
	//previousNode = parent_;
}

#pragma endregion
