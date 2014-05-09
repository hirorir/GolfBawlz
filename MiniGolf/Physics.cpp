#include "Physics.h"

using namespace physics;
using namespace glm;

vec3 PhysicsObject::get_velocity(){
	return velocity;
}

void PhysicsObject::applyForce(vec3 force){
	velocity += force / mass * timestep;		//This is essentially impulse which is instantaneous force integrated according to dt, divided by mass to get dv
}

vec3 PhysicsObject::update(vec3 position, vec3 velocity){
	position += velocity * timestep;
	return position;
}

void Collision::generateCollisions(){
	
}

void Collision::resolveCollision(){
	//stub
}