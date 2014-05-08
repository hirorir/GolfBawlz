#include "Physics.h"

using namespace physics;
using namespace glm;

void PhysicsObject::applyForce(vec3 force){
	velocity += force / mass * timestep;		//This is essentially impulse which is instantaneous force integrated according to dt, divided by mass to get dv
}

void PhysicsObject::update(){
	position += velocity * timestep;
}

void Collision::generateCollisions(){
	//stub
}