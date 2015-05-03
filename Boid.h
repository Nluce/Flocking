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
	bool offScreen = false;

	const float maxSpeed = 120;
	const vec2 center = vec2(640, 480) / 2.0f;

	void Draw()
	{
	}

	void PreMove(){
		newVelocity = velocity;

		const int border = 50;
		const float turningForce = 0.5;
		offScreen = false;
		// keep the boids on the screen
		if (position.x < border) 
		{
			newVelocity.x += turningForce;
			offScreen = true;
		}
		if (position.x > 640 - border)
		{
			newVelocity.x -= turningForce;
			offScreen = true;
		}
		if (position.y < border)
		{
			newVelocity.y += turningForce;
			offScreen = true;
		}

		if (position.y > 480 - border) 
		{
			newVelocity.y -= turningForce;
			offScreen = true;
		}


	}

	void Chase(const Boid & otherBoid)
	{
		if (offScreen)
		{
			//If the hawk is off screen don't bother chasing birds.
			return;
		}
		//Calculate the distance to the bird
		vec2 d = otherBoid.position - position;
		float len = length(d);

		// how far the hawk can see
		const float eyeSightLimit = 130; 

		//Importance of chasing to the hawk
		const float chaseForce = 0.9;

		//check to see if the hawk can see the bird
		if (len < eyeSightLimit)
		{
			//make the hawk go in the direction of the bird.
			newVelocity += normalize(d) * chaseForce;
		}
	}

	void Evade(const Boid & otherBoid)
	{
		//Very similar to chase execept some changes in values,
		//and the velocity change is moving in the opposite direction of the bird
		vec2 d = otherBoid.position - position;
		float len = length(d);

		const float eyeSightLimit = 100; // how far the boid can see

		const float evadeForce = 1.9;

		if (len < eyeSightLimit)
		{
			//note the "-="
			newVelocity -= normalize(d) * evadeForce;
		}
	}

	void FlockTogether(const Boid & otherBoid)
	{
		//if the bird is off the screen, don't bother flocking
		if (offScreen)
		{
			return;
		}
		//this calculates the distance to the other bird
		vec2 d = otherBoid.position - position;
		float len = length(d);

		const float eyeSightLimit = 100; // how far the boid can see


		const float spacingMin = 20; // how far away from each other they want to be
		const float moveApartForce = 0.9;

		const float spacingMax = 90; // how far away from each other they want to be
		const float moveTogetherForce = 0.1;


		const float flockingRange = 50; // how close they have to be to follow their neighbor
		const float flockingForce = 0.3;

		if (len < eyeSightLimit){
			// bird can see the other bird

			//If they are too close they try to move apart
			if (len < spacingMin)
			{
				newVelocity -= normalize(d) * moveApartForce;
			}
			//If they are too far apart they try tro move together
			if (len > spacingMax)
			{
				newVelocity += normalize(d) * moveTogetherForce;
			}
			//If they are in the flocking distance they try to align
			if (len < flockingRange)
			{
				//make sure the other bird is moving
				if (length(otherBoid.velocity) > 0)
				{
					//normaalizes the velocity of the other bird and adds it to the current bird.
					newVelocity += normalize(otherBoid.velocity) * flockingForce;
				}
			}
		}
	}

	void HawkAntiFlock(const Boid & otherBoid)
	{
		//don't flock if hawk is offscreen
		if (offScreen) 
		{
			return;
		}

		vec2 d = otherBoid.position - position;
		float len = length(d);

		const float eyeSightLimit = 130; // how far the boid can see

		const float spacingMin = 90; // how far away from each other they want to be
		const float moveApartForce = 0.9;

		// boid can see the other boid
		if (len < eyeSightLimit)
		{
			

			if (len < spacingMin)
			{
				newVelocity -= normalize(d) * moveApartForce;
			}
		}
	}

	void Move(float elapsedTime)
	{
		velocity = newVelocity;
		//make sure the bird/hawk isn't going too fast (sets to max speed if over)
		if (length(velocity) > maxSpeed)
		{
			velocity = normalize(velocity) * maxSpeed;
		}
		//move routine
		position += velocity * elapsedTime;
	}



};

