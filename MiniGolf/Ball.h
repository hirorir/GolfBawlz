#ifndef BALL_H
#define BALL_H

#include "Object3D.h"

#define PI 3.141592653589793

class Ball : public Object3D
{
public:
	Ball();

	Ball(int tile_id, vec3 position);

	virtual void init_gl();

	virtual void draw(Camera *camera, Light *light);

private:
	GLuint nVerts, elements;
	float radius, slices, stacks;

	void generate_verts(float * verts, float * norms, float * tex, unsigned int * el);
};
#endif