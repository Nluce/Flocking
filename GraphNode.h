#pragma once
#include <string>
#include "GraphNode.h"
#include "Edge.h"
#include <vector>
#include <iostream>
#include <glm/glm.hpp>

using namespace std;

class GraphNode
{
	typedef std::vector<Edge> EdgeList;
public:
	int nodeNumber;
	
	EdgeList edges;
	int stepCount;

	bool visited;

	// used in A*
	bool inOpenSet;
	bool inClosedSet;
	GraphNode* cameFrom;
	float gScore;
	float fScore;





	glm::ivec2 position;
	GraphNode(int num)
	{
		nodeNumber = num;
	}


	void AddEdge(const Edge & edge)
	{
		edges.push_back(edge);
	}

	void PrintNeighbors()
	{
		cout << "Neighbors of node " << nodeNumber << ":" << endl;
		for (Edge edge : edges){
			cout << " node " << edge.end->nodeNumber << endl;
		}
	}

	bool GoesTo(GraphNode * otherNode)
	{
		for (Edge edge : edges)
		{
			if (edge.end == otherNode)
			{
				return true;
			}
		}
		return false;
	}


	bool IsNeighbor(GraphNode * otherNode)
	{
		return otherNode->GoesTo(this) || this->GoesTo(otherNode);
	}


	float distanceTo(glm::ivec2 otherPoint)
	{
		glm::vec2 v = position - otherPoint;
		return glm::length(v);
	}

	bool operator<(GraphNode * other)
	{
		if (fScore == other->fScore){
			return nodeNumber < other->nodeNumber;
		}
		return fScore < other->fScore;
	}

};
