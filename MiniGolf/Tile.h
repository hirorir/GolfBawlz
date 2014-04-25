#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <glm\glm.hpp>

#include "Material.h"
#include "Shader.h"

using namespace std;
using namespace glm;

class Tile
{
public:
	Tile(int tile_id, int vertex_count, int edge_count, vector<float> verticies, vector<int> neighbors);

	void draw(Shader *shader);

	void print();

	int get_tile_id();

	int get_vertex_count();

	int get_edge_count();

	vector<float> get_verticies();

	vector<int> get_neighbors();

	vec3 get_normal();

	Material get_material();

	void set_material(Material mat);

	void set_shader_uniforms(Shader *shader, Material mat);

private:
	GLuint tile_vao;
	GLuint border_vao;
	int tile_id;
	int vertex_count;
	int edge_count;
	vector<float> vertices;
	vector<float> edges;
	vector<int> neighbors;
	vec3 normal;
	Material material;

	vector<float> calculate_edges();
	vec3 calculate_normal();
	void init_gl_tile();
	void init_gl_border();
	void draw_tile(Shader *shader);
	void draw_border(Shader *shader);
};

#endif