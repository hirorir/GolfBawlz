#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <glm\glm.hpp>

#include "Object3D.h"
#include "Material.h"
#include "Shader.h"
#include "Border.h"
#include "Plane.h"

using namespace std;
using namespace glm;

class Tile : public Plane
{
public:
	Tile();

	Tile(int id, int edge_count, vector<vec3> verticies, vector<int> neighbors);

	~Tile();

	virtual void draw(Camera *camera, Light *light);

	float get_friction();

	vector<Border*> get_borders();

	vector<int> get_neighbors();

private:
	vector<Border*> borders;

	int edge_count;

	vector<vec3> vertices;

	vector<int> neighbors;

	void init_gl();

	float friction;

	void init_borders();
};

#endif