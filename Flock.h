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
		for (int i = 0; i < 2; i++){
			Boid * boid = new Boid();
			int x = rand() % 640;
			int y = rand() % 480;

			boid->position = vec2(x, y);

			hawklist.push_back(boid);
		}
	}

	void move(float elapsedTime){

		for (auto boid : boidList){
			boid->PreMove();
		}

		for (auto hawk : hawklist){
			hawk->PreMove();
		}


		for (auto hawk : hawklist){
			for (auto boid2 : boidList){
				hawk->Chase(*boid2);
				boid2->Evade(*hawk);
			}

			for (auto hawk2 : hawklist){
				if (hawk != hawk2){
					hawk->HawkFlock(*hawk2);
				}
			}
		}



		for (auto boid : boidList){
			for (auto boid2 : boidList){
				if (boid != boid2){
					boid->FlockTogether(*boid2);
				}
			}
		}



		for (auto boid : boidList){
			boid->Move(elapsedTime);
		}
		for (auto boid : hawklist){
			boid->Move(elapsedTime);
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
		for (auto boid : hawklist){
			copSprite.setPosition(boid->position);

			float angle = atan2(boid->velocity.y, boid->velocity.x);
			float d = degrees(angle);
			copSprite.setRotation(d);

			copSprite.draw();
		}
	}

};