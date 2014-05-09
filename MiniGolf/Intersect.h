#ifndef INTERSECT_H
#define INTERSECT_H

#include "Object3D.h"
#include "Ball.h"
#include "Tile.h"

class Intersect {
public:
	static bool sphere_plane(Ball *ball, Tile *tile);
	static float isect_sphere_plane(vec3 s_pos, float s_rad, vec3 s_vel, vec3 plane_normal, vector<vec3> plane_vertices);
};

#endif