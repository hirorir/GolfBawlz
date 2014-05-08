#ifndef BALL_H
#define BALL_H

#include "Object3D.h"

#define PI 3.141592653589793

class Ball : public Object3D
{
public:
	Ball();

	Ball(int tile_id, vec3 position, char *vtx_path, char *frg_path);

	virtual void draw(Camera *camera, Light *light);

	float get_radius();

private:
	GLuint nVerts, elements;
	float radius, slices, stacks;

	void init_gl();
	void generate_verts(float * verts, float * norms, float * tex, unsigned int * el);
};
#endif