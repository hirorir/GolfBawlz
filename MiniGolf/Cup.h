#ifndef CUP_H
#define CUP_H

#include "Object3D.h"

class Cup : public Object3D
{
public:
	Cup();

	Cup(int tile_id, vec3 position);

	virtual void init_gl();

	virtual void draw(Camera *camera, Light *light);
};

#endif