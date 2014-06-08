#ifndef CUP_H
#define CUP_H

#include "Object3D.h"
#include "Ball.h"

class Cup : public Object3D
{
public:
	Cup();

	~Cup();

	Cup(int tile_id, vec3 position);

	virtual void draw(Camera *camera, Light *light);

	Ball *get_sphere() const;

private:
	void init_gl();
	Ball *isect_sphere;
};

#endif