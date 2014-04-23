#ifndef CUP_H
#define CUP_H

#include "Object3D.h"

class Cup : public Object3D
{
public:
	Cup();

	Cup(vector<float> position, int tile_id) : Object3D(position, tile_id) {}

	void init_gl()
	{

	}

	void draw()
	{

	}
};

#endif