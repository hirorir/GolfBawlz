#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <glm\glm.hpp>

#include "Object3D.h"
#include "Ball.h"
#include "Material.h"
#include "Shader.h"

using namespace std;
using namespace glm;

class Tile : public Object3D
{
public:
	Tile(int id, int edge_count, vector<float> verticies, vector<int> neighbors, char *vtx_path, char *frg_path);

	virtual void draw(Camera *camera, Light *light);

	void print();

	int num_of_edge_indices();

	vector<float> get_vertices();

	vector<int> get_neighbors();

	vec3 get_normal();

private:
	GLuint tile_vao;
	GLuint border_vao;

	int num_edge_indices;

	vector<float> vertex_indices;
	vector<float> edge_indices;
	vector<int> neighbors;

	vec3 normal;

	vector<float> calculate_edges();
	vec3 calculate_normal();

	void init_gl_tile();
	void init_gl_border();
};

#endif