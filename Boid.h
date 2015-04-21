#pragma once
#include <glm\glm.hpp>

using namespace glm;

class Boid
{
public:
	Boid();
	~Boid();
	vec2 position = vec2();
	vec2 velocity = vec2();
	vec2 newVelocity = vec2();

	const float maxSpeed = 70;
	const vec2 center = vec2(640, 480) / 2.0f;

	void Draw()
	{
	}

	void PreMove(){
		newVelocity = velocity;


		// keep the boids on the screen
		if (position.x < 0) {
			newVelocity.x += 0.5;
		}

		if (position.x > 640) {
			newVelocity.x -= 0.5;
		}
		if (position.y < 0) {
			newVelocity.y += 0.5;
		}

		if (position.y > 480) {
			newVelocity.y -= 0.5;
		}


	}

	void FlockTogether(const Boid & otherBoid){
		vec2 d = otherBoid.position - position;
		float len = length(d);

		const float eyeSightLimit = 100; // how far the boid can see
		const float spacingMin = 30; // how far away from each other they want to be
		const float spacingMax = 90; // how far away from each other they want to be
		const float flockingRange = 40; // how close they have to be to follow their neighbor

		if (len < eyeSightLimit){
			// boid can see the other boid


			if (len < spacingMin){
				newVelocity -= normalize(d) * 0.9f;
			}
			if (len > spacingMax){
				newVelocity += normalize(d) * 0.1f;
			}

			if (len < flockingRange){
				if (length(otherBoid.velocity) > 0){
					newVelocity += normalize(otherBoid.velocity) * 0.1f;
				}
			}
		}
	}

	void Move(float elapsedTime){
		velocity = newVelocity;
		if (length(velocity) > maxSpeed){
			velocity = normalize(velocity) * maxSpeed;
		}
		position += velocity * elapsedTime;
	}



};

