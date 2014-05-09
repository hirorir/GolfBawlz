#ifndef INTERSECT_H
#define INTERSECT_H

#include "Object3D.h"
#include "Ball.h"
#include "Tile.h"

class Intersect {
public:
	static bool sphere_plane(Ball *ball, Tile *tile);
};

#endif