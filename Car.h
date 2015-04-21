#pragma once
#include "GraphNode.h"
#include "Graph.h"
#include <glm\glm.hpp>

using namespace glm;
class NodeCity;

class Car
{
public:
	NodeCity* city;
	vector <GraphNode *> path;
	int currentCheckpoint = 0;
	int currentPathNode = 0;
	glm::vec2 position;
	glm::vec2 direction;

	Car(){}
	~Car();
	void move();


};

