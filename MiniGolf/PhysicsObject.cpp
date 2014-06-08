#include "PhysicsObject.h"


PhysicsObject::PhysicsObject()
{
	velocity = vec3(0.0f); // No initial velocity.
	angle = (float)2.5; // Starting at about a 45 degree angle.

	timer.start(); // Start the timer.
	last_time = timer.get_elapsed_time_in_sec(); // Set the initial time step.
}


vec3 PhysicsObject::get_velocity()
{
	return velocity;
}

void PhysicsObject::set_velocity(vec3 v)
{
	velocity = v;
}

void PhysicsObject::add_force(vec3 f)
{
	forces.push(f); // Add force to queue.
}

void PhysicsObject::add_force()
{
	vec3 f = vec3(18.f, 0.0f, -21.f);
 	forces.push(f);
}

vec3 PhysicsObject::euler_integration(vec3 position, vec3 velocity, float t)
{
	return position + velocity * t;
}

// Calculate the 'influence' of gravity on this plane.
vec3 PhysicsObject::plane_gravity_direction(vec3 plane_normal)
{
	vec3 p = cross(plane_normal, vec3(0.0f, 1.0f, 0.0f));
	vec3 g = cross(plane_normal, p);

	return normalize(g);
}

// Calcualte the reflection.
vec3 PhysicsObject::plane_reflection_velocity(vec3 velocity, vec3 plane_normal)
{
	vec3 d = normalize(velocity);
	float magnitude = (float)glm::sqrt(dot(velocity, velocity));

	cout << "Reflection Magnitude: " << magnitude << endl;

	// r = 2(n dot -l)n + l
	vec3 reflect = 2 * dot(plane_normal, -d) * plane_normal + d;

	return magnitude * reflect;
}

// Calculate the time of sphere-plane intersection.
float PhysicsObject::isect_sphere_plane(vec3 s_pos, float s_rad, vec3 s_vel, vec3 plane_normal, vector<vec3> plane_vertices)
{
	vec3 sphere_plane_offset = s_rad * plane_normal;

	for (vector<vec3>::size_type i = 0; i < plane_vertices.size(); ++i) {
		plane_vertices[i] += sphere_plane_offset;
	}

	float offset_plane_distance = -dot(plane_normal, plane_vertices[0]);

	return -(dot(plane_normal, s_pos) + offset_plane_distance) / dot(s_vel, plane_normal);
}

// Calculate some friction.
vec3 PhysicsObject::friction(vec3 vel, float mag)
{
	if (!glm::sqrt(dot(vel, vel))) {
		return vec3(0.0f);
	}
	return -normalize(vel) * mag;
}

bool PhysicsObject::isect_sphere_sphere(vec3 p1, float r1, vec3 p2, float r2)
{
	vec3 diff = p1 - p2;

	return (glm::sqrt(dot(diff, diff)) <= (r1 + r2));
}