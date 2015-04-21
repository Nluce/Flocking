#include "Boid.h"
#include "Shape.h"
#include "Sprite.h"


class Flock {
	std::vector<Boid*> boidList;
	std::vector<Boid*> hawklist;


	Texture redCarTexture = Texture("redCar.png");
	Shape boidShape = Shape(&redCarTexture);
	Sprite boidSprite = Sprite(&boidShape);

	Texture copTexture = Texture("CopCar.png");
	Shape copShape = Shape(&copTexture);
	Sprite copSprite = Sprite(&copShape);
public:
	Flock(){
		for (int i = 0; i < 100; i++){
			Boid * boid = new Boid();
			int x = rand() % 640;
			int y = rand() % 480;

			boid->position = vec2(x, y);

			boidList.push_back(boid);
		}
	}

	void move(float elapsedTime){
		for (auto boid : boidList){
			for (auto boid2: boidList){
				if (boid != boid2){
					boid->Move(*boid2);
				}
			}
		}

		for (auto boid : boidList){
			boid->position += boid->velocity * elapsedTime;
		}
	}

	void draw()
	{
		for (auto boid : boidList){
			boidSprite.setPosition(boid->position);

			float angle = atan2(boid->velocity.y, boid->velocity.x);
			float d = degrees(angle);
			boidSprite.setRotation(d);

			boidSprite.draw();
		}
	}

};