#include "Tee.h"

Tee::Tee() {}

Tee::Tee(int id, vec3 position, vector<vec3> verts) : Plane(id, position, verts)
{
	material = new Material(vec3(0.1f, 0.1f, 1.0f), vec3(0.1f, 0.1f, 1.0f), vec3(0.0f), 100.0f);
	init_gl();
}