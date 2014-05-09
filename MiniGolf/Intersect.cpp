#include "Intersect.h"

bool Intersect::sphere_plane(Ball *ball, Tile *tile)
{
	vec3 tmp = ball->get_position() - tile->get_position();

	float dist = dot(tmp, tile->get_normal());

	if (dist > ball->get_radius()) {
		return false;
	}

	return true;
}