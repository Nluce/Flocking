#include "Boids.h"
#include "Shape.h"
#include "Sprite.h"

Texture redCarTexture = Texture("redCar.png");
Shape boidShape = Shape(&redCarTexture);
Sprite boidSprite = Sprite(&boidShape);

Texture copTexture = Texture("CopCar.png");
Shape copShape = Shape(&copTexture);
Sprite copSprite = Sprite(&copShape);

class Flock {
	std::vector<Boids*> boidList;
	std::vector<Boids*> hawklist;
public:

	

	void draw()
	{

	}

};