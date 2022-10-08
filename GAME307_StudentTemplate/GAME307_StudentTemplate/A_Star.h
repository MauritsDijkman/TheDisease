#ifndef A_STAR_H
#define A_STAR_H

#include "MMath.h"
#include "Node.h"
#include <list>
#include <vector>

using namespace MATH;
using namespace std;

class A_Star {
private:
	//list<int> visitedNodes;
	//list<int> unvisitedNodes;

	vector<Node> visitedNodes;		// Open list
	vector<Node> unvisitedNodes;	// Closed list

	// All the nodes on the board
	Node nodes[1];
	Node startNode;
	Node targetNode;

	Node GetLowestDistance(vector<Node> nodes);
	vector<Node> FindParent(Node currentNode);

	bool inUnvisitedList;
	bool inVisitedList;

public:
	A_Star();
	~A_Star();

	bool OnCreate();
	//void OnDestroy();

	//void Update(const float time);

	void SetNodeList(Node nodes[]);
};

#endif
