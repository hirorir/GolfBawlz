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

class Tile : public Object3D, public Plane
{
public:
	Tile();

	Tile(int id, int edge_count, vector<float> verticies, vector<int> neighbors, char *vtx_path, char *frg_path);

	~Tile();

	virtual void draw(Camera *camera, Light *light);

	void print();

	float get_friction();

	vector<Border*> get_borders();

	vector<int> get_neighbors();

private:
	vector<Border*> borders;

	int num_edge_indices;

	vector<float> vertex_indices;

	vector<float> edge_indices;

	vector<int> neighbors;

	vector<float> calculate_edges();

	void init_gl();

	float friction;

	void init_borders(char *vtx_path, char *frg_path);
};

#endif