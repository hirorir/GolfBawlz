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

using namespace std;
using namespace glm;

class Tile : public Object3D
{
public:
	Tile(int tile_id, int position_indices, int edge_count, vector<float> verticies, vector<int> neighbors);

	virtual void draw(Camera *camera, Light *light);

	void print();

	int get_tile_id();

	int num_of_pos_indices();

	int num_of_edge_indices();

	vector<float> get_verticies();

	vector<int> get_neighbors();

	vec3 get_normal();

	Material get_material();

	void set_material(Material mat);

private:
	GLuint tile_vao;
	GLuint border_vao;

	int num_position_indices;
	int num_edge_indices;

	vector<float> vertices;
	vector<float> edges;
	vector<int> neighbors;

	vec3 normal;
	Material material;

	vector<float> calculate_edges();
	vec3 calculate_normal();

	void init_gl_tile();
	void init_gl_border();
};

#endif