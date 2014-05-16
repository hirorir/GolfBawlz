#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include <glm\glm.hpp>

#include "PhysicsObject.h"

using namespace glm;
using namespace std;

#define PI 3.141592653589793

class Plane
{
public:
	Plane();

	Plane(vector<float> verts);

	bool point_in_plane(vec3 point);

	vector<vec3> get_vertices();

	vec3 get_normal();

	bool sloped();

	float get_dist_from_origin();

	vec3 get_direction_gravity();

protected:
	vector<vec3> vertices;

	float dist_from_origin;

	bool is_sloped;

	vec3 direction_gravity;

	vec3 normal;

	vec3 calculate_normal();

private:
	vec3 min_vec;

	vec3 max_vec;

	void calculate_vertices(vector<float> verts);

};

#endif