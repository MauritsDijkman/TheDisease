//#include "A_Star.h"
//
//A_Star::A_Star() {}
//
//A_Star::~A_Star() {}
//
//bool A_Star::OnCreate()
//{
//	// Set the target node for every node in the scene
//	for (Node node_ : nodes) {
//		//node_.SetTargetNode(targetNode);
//	}
//
//	// Create a current node to work with
//	Node currentNode = startNode;
//
//	// Add the current node to the unvisited list (will be the first node in the list)
//	unvisitedNodes.insert(unvisitedNodes.end(), currentNode);
//
//	// While the list is not empty, calculate the paths
//	while (unvisitedNodes.size() > 0)
//	{
//		// Calculate the G value for every node
//		for (Node node : unvisitedNodes)
//			node.Get_G();
//
//		// Set the current node to the node with the lowest distance
//		currentNode = GetLowestDistance(unvisitedNodes);
//
//		unvisitedNodes.erase(unvisitedNodes.begin());			// Remove the current node from the list
//		visitedNodes.insert(visitedNodes.end(), currentNode);	// Add the current node to the done list
//
//		// Create the position values for checking later
//		Vec3 currentPos = currentNode.GetPos();
//		Vec3 targetPos = targetNode.GetPos();
//
//		// Check if the current node is the target node
//		if (currentPos == targetPos)
//		{
//			// Return a list with all the nodes of the shortest path
//			vector<Node> route = FindParent(currentNode);
//			//return route;
//		}
//		else
//		{
//			for (Node connectedNode : currentNode.GetConnections())
//			{
//				// Check if the connectedNode is in the list with unvisitedNodes
//				for (Node currentNode_ : unvisitedNodes)
//				{
//					if (currentNode.GetPos() == connectedNode.GetPos())
//					{
//						inUnvisitedList = true;
//						break;
//					}
//					else
//						inUnvisitedList = false;
//				}
//
//				// Check if the connectedNode is in the list with visitedNodes
//				for (Node currentNode_ : visitedNodes)
//				{
//					if (currentNode.GetPos() == connectedNode.GetPos())
//					{
//						inVisitedList = true;
//						break;
//					}
//					else
//						inVisitedList = false;
//				}
//
//				// Checks if the todo or done lists don't already contain the node, also checks if the node is not locked
//				if (!inUnvisitedList && !inVisitedList)
//				{
//					connectedNode.SetParent(connectedNode);
//					unvisitedNodes.insert(unvisitedNodes.end(), connectedNode);
//				}
//			}
//		}
//	}
//
//	/**
//	// Add all the nodes to the unvisited list
//	for (int i = 0; i < sizeof(nodes); i++)
//		unvisitedNodes.insert(unvisitedNodes.end(), nodes[i]);
//
//	// Set the target node and h value for each node (distance from node to target node)
//	for (Node node_ : unvisitedNodes)
//		node_.SetTargetNode(targetNode);
//
//	// Put the starting node on the visited list (you can leave its f at zero)
//	unvisitedNodes.erase(unvisitedNodes.begin());
//	visitedNodes.insert(visitedNodes.end(), nodes[0]);
//
//	while (unvisitedNodes.size() > 0)
//	{
//		// Assign a value to q
//		Node q = visitedNodes[0];
//
//		// Find the node with the lowest f on the open list
//		for (int i = 0; i < unvisitedNodes.size(); i++)
//		{
//			if (q.Get_F() < unvisitedNodes[i].Get_F())
//				q = unvisitedNodes[i];
//		}
//
//		// Remove q from the open list
//		//unvisitedNodes.erase(q);
//	}
//	/**/
//
//return false;
//}
//
//Node A_Star::GetLowestDistance(vector<Node> nodes)
//{
//	// Create new node and set to the first one in the list
//	Node nodeLowestDistance = nodes[0];
//
//	// Check for each node in the list if the distance is smaller
//	// then the already existing list
//	for (int i = 0; i < nodes.size(); i++)
//	{
//		if (nodes[i].Get_F() < nodeLowestDistance.Get_F())
//			nodeLowestDistance = nodes[i];
//	}
//
//	return nodeLowestDistance;
//}
//
//vector<Node> A_Star::FindParent(Node currentNode)
//{
//	// While the previous node has a parent, add it too the list
//	if (currentNode.GetPreviousNode() != NULL)
//	{
//		//vector<Node> list = FindParent(currentNode.GetPreviousNode());
//		vector<Node> list;
//		list.insert(list.end(), currentNode);
//		return list;
//	}
//	else
//	{
//		vector<Node> list = vector<Node>();
//		list.insert(list.end(), currentNode);
//		return list;
//	}
//}
//
//void A_Star::SetNodeList(Node nodes_[])
//{
//	//nodes = nodes_;
//	//copy(begin(nodes), std::end(nodes), begin(nodes_));
//}
