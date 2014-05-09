#include "Intersect.h"

bool Intersect::sphere_plane(Ball *ball, Tile *tile) 
{
	vec3 tmp = ball->get_position() - tile->get_position();

	float dist = dot(tmp, tile->get_normal());

	if (dist > ball->get_radius()) {
		return false;
	} else return true;

	//need to change to projection instead of distance between two points. http://codereview.stackexchange.com/questions/9672/sphere-plane-collision-test
}

float isect_sphere_plane(vec3 s_pos, float s_rad, vec3 s_vel, vec3 plane_normal, vector<vec3> plane_vertices)
{
	vec3 sphere_plane_offset = s_rad * plane_normal;

	for (vector<vec3>::size_type i = 0; i < plane_vertices.size(); ++i) {
		plane_vertices[i] += sphere_plane_offset;
	}

	float offset_plane_distance = -dot(plane_normal, plane_vertices[0]);

	return -(dot(plane_normal, s_pos) + offset_plane_distance) / dot(plane_normal, s_vel);
}