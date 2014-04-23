#ifndef TEE_H
#define TEE_H

#include "Object3D.h"

class Tee : public Object3D
{
public:
	Tee();

	Tee(vector<float> position, int tile_id) : Object3D(position, tile_id) {}

	void init_gl()
	{

	}

	void draw()
	{

	}
};

#endif