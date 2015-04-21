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

	const float maxSpeed = 120;
	const vec2 center = vec2(640, 480) / 2.0f;

	void Draw()
	{
	}

	void PreMove(){
		newVelocity = velocity;

		const int border = 100;
		const float turningForce = 0.8;
		// keep the boids on the screen
		if (position.x < border) {
			newVelocity.x += turningForce;
		}
		if (position.x > 640 - border) {
			newVelocity.x -= turningForce;
		}
		if (position.y < border) {
			newVelocity.y += turningForce;
		}

		if (position.y > 480 - border) {
			newVelocity.y -= turningForce;
		}


	}

	void FlockTogether(const Boid & otherBoid){
		vec2 d = otherBoid.position - position;
		float len = length(d);

		const float eyeSightLimit = 100; // how far the boid can see


		const float spacingMin = 20; // how far away from each other they want to be
		const float moveApartForce = 0.9;

		const float spacingMax = 90; // how far away from each other they want to be
		const float moveTogetherForce = 0.1;


		const float flockingRange = 50; // how close they have to be to follow their neighbor
		const float flockingForce = 0.05;

		if (len < eyeSightLimit){
			// boid can see the other boid


			if (len < spacingMin){
				newVelocity -= normalize(d) * moveApartForce;
			}

			if (len > spacingMax){
				newVelocity += normalize(d) * moveTogetherForce;
			}

			if (len < flockingRange){
				if (length(otherBoid.velocity) > 0){
					newVelocity += normalize(otherBoid.velocity) * flockingForce;
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

