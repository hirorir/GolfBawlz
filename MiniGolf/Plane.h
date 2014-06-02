#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include <glm\glm.hpp>

#include "Object3D.h"
#include "PhysicsObject.h"

using namespace glm;
using namespace std;

class Plane : public Object3D
{
public:
	Plane();

	Plane(int id, vec3 position, vector<vec3> verts);

	Plane(int id, vec3 position);

	virtual void draw(Camera *camera, Light *light);

	vector<vec3> get_vertices();

	vec3 get_normal();

	bool sloped();

	float get_dist_from_origin();

	vec3 get_direction_gravity();

protected:
	int faces;

	vector<vec3> vertices;

	float dist_from_origin;

	bool is_sloped;

	vec3 direction_gravity;

	vec3 normal;

	vec3 min_vec;

	vec3 max_vec;

	vec3 calculate_normal();

	void init_gl();
};

#endif