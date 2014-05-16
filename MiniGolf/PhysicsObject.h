#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <queue>
#include <glm\glm.hpp>

#include "Timer.h"

using namespace glm;

enum PhysicsType : int{
	DEFAULT = 0,
	PLANE = 1,
	SPHERE = 2,
};

class PhysicsObject
{
public:
	PhysicsObject(); // Constructor.

	virtual void run_simulation() = 0; // Every physics object must have a simulation.

	vec3 get_velocity();

	void set_velocity(vec3 v);

	void add_force(vec3 f);

	void add_force();

	float sin_angle(float a);

	float cos_angle(float a);

	// General Static Functions for all things Physics.

	static vec3 euler_integration(vec3 position, vec3 velocity, float t); // Integrator.

	static vec3 plane_gravity_direction(vec3 plane_normal); // Get the direction of gravity influence on a plane.

	static vec3 plane_reflection_velocity(vec3 velocity, vec3 plane_normal); // Get the reflection vector.

	static float isect_sphere_plane(vec3 s_pos, float s_rad, vec3 s_vel, vec3 plane_normal, vector<vec3> plane_vertices); // Sphere-Plane intersection test.

	static vec3 friction(vec3 vel, float mag); // Calculates friction.

protected:
	// Physics members.
	vec3 velocity;
	queue<vec3> forces; // Accumulate forces.
	float angle; // Angle of this object.
	PhysicsType type; // What kind of physics object is this?

	// Timimg members.
	Timer timer; // This physics objects timer.
	double last_time; // The last time step.
};

#endif