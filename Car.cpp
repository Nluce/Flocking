#include "Car.h"

#include "NodeCity.h"
#include "Game.h"



Car::~Car()
{
}


void Car::move()
{
	float et = theGame.elapsedTime;

	GraphNode * node = city->graph.FindClosestNode(position);
	GraphNode * pathNode = nullptr;

	if (currentPathNode < path.size())
	{
		pathNode = path[currentPathNode];
		if (pathNode == node)
		{
			currentPathNode++;
			if (currentPathNode < path.size())
			{
				pathNode = path[currentPathNode];
			}
			else {
				pathNode = nullptr;
			}
		}
	}


	// check if we made it to the end of our path.
	if (pathNode == nullptr)
	{
		GraphNode * checkPointNode = city->checkpoints[currentCheckpoint];

		// check to see if we made it to our checkpoint...
		if (node == checkPointNode){
			currentCheckpoint++;
			if (currentCheckpoint >= city->checkpoints.size())
			{
				// if we make it to the last checkpoint, then we restart at checkpoint[0]
				currentCheckpoint = 0;
			}
			checkPointNode = city->checkpoints[currentCheckpoint];
		}

		// make a new path.
		path = city->graph.AStar(node, checkPointNode);
		if (path.size() == 0){
			cout << "Error: can find path" << endl;
			return;
		}
		currentPathNode = 0;
	}

	// try to move to the next node in the path...
	pathNode = path[currentPathNode];

	// destination is where we want to move to
	glm::vec2 destination = pathNode->position;

	// direction is a vector to the destination... 
	direction = destination - position;

	if (glm::length(direction) > 0.0){
		// normalize() changes the length of the vector to 1.0
		direction = glm::normalize(direction);


		float speed = 60;
		float movement = speed * et;

		if (movement > NodeCity::TILE_SIZE)
		{
			movement == NodeCity::TILE_SIZE;
		}
		direction *= movement;
		position += direction;
	}

}

