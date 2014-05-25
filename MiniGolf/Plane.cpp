#include "Plane.h"

Plane::Plane() {}

Plane::Plane(vector<vec3> verts)
{
	vertices = verts;

	normal = calculate_normal();

	dist_from_origin = -dot(normal, vertices[0]);

	min_vec = max_vec = vertices[0];
	for (vector<vec3>::size_type i = 0; i < vertices.size(); ++i) {
		vec3 v = vertices[i];

		if (v.x < min_vec.x) { 
			min_vec.x = v.x; 
		}
		else if (v.x > max_vec.x) { 
			max_vec.x = v.x; 
		}

		if (v.y < min_vec.y) { 
			min_vec.y = v.y; 
		}
		else if (v.y > max_vec.y) {
			max_vec.y = v.y; 
		}

		if (v.z < min_vec.z) { 
			min_vec.z = v.z; 
		}
		else if (v.z > max_vec.z) { 
			max_vec.z = v.z; 
		}
	}

	if (min_vec.y == max_vec.y) {
		direction_gravity = vec3(0.0f);
		is_sloped = false;
	}
	else {
		direction_gravity = PhysicsObject::plane_gravity_direction(normal);
		is_sloped = true;
	}
}

vector<vec3> Plane::get_vertices()
{
	return vertices;
}

vec3 Plane::get_normal()
{
	return normal;
}

bool Plane::sloped()
{
	return is_sloped;
}

float Plane::get_dist_from_origin()
{
	return dist_from_origin;
}

vec3 Plane::calculate_normal()
{
	if (vertices.size() < 3) {
		cout << "error - not enough vertices in this Plane to calculate the normals." << endl;
		return vec3(0.0f, 1.0f, 0.0f); // Just assume 'up' vector if we have an error.
	}
	vec3 v1 = vertices[0], v2 = vertices[1], v3 = vertices[2];

	vec3 a = v2 - v1;
	vec3 b = v3 - v1;

	return normalize(cross(a, b));
}

vec3 Plane::get_direction_gravity()
{
	return direction_gravity;
}

bool Plane::point_in_plane(vec3 point)
{
	if (point.x < min_vec.x || point.z < min_vec.z || point.x > max_vec.x || point.z > max_vec.z) {
		return false;
	}
	return true;
}