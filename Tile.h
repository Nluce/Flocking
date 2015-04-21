#pragma once
#include <string>
#include "GraphNode.h"
#include "Edge.h"
#include <vector>
#include <iostream>
class Tile
{
public:
	Tile();
	~Tile();

	GraphNode* nodes[4];

};

