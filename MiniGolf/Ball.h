#ifndef BALL_H
#define BALL_H

#include "Object3D.h"

#define PI 3.141592653589793

class Ball : public Object3D
{
public:
	Ball();

	Ball(int tile_id, vec3 position, float r, float sl, float st);

	Ball(int tile_id, vec3 position) : Object3D(tile_id, position) {
		// Default ball values.
		radius = 0.2f;
		slices = 40;
		stacks = 40;
	}

	virtual void init_gl();

	virtual void draw(Shader *shader);

	virtual void set_shader_uniforms(Shader *shader, Material mat);

	void generate_verts(float * verts, float * norms, float * tex, unsigned int * el);

	void set_radius(float r);
	
	void set_slices(float sl);

	void set_stacks(float st);

protected:
	typedef Object3D super;
	GLuint nVerts, elements;
	float radius, slices, stacks;
};
#endif