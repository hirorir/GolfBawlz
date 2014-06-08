#ifndef BALL_H
#define BALL_H

#include "Object3D.h"
#include "PhysicsObject.h"
#include "Tile.h"

#include <glm\glm.hpp>

#define PI 3.141592653589793

using namespace glm;

class Ball : public Object3D, public PhysicsObject
{
public:
	Ball();

	Ball(int tile_id, vec3 pos);

	virtual void draw(Camera *camera, Light *light);

	float get_radius() const;

	void set_radius(float r);

	virtual void run_simulation(); // Run physics simulation;

	void set_current_tile(Tile *tile);

	bool collide_with_edge(double time_elapsed);

	bool is_active() const;

private:
	Tile *t;

	GLuint nVerts, elements;
	float radius, slices, stacks;

	void init_gl();
	void generate_verts(float * verts, float * norms, float * tex, unsigned int * el);
	bool active;
};

#endif