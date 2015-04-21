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

	void Draw()
	{
		
	}

	void Move(const Boid & otherBoid){
		vec2 d = otherBoid.position - position;
		velocity += normalize(d);
	}
};

