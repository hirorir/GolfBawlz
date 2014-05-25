#include "Tile.h"

Tile::Tile() {}

Tile::Tile(int id, int ecount, vector<vec3> verts, vector<int> nbors, char *vtx_path, char *frg_path) : Object3D(id, vtx_path, frg_path), Plane(verts)
{
	edge_count = ecount;
	vertices = verts;
	neighbors = nbors;

	init_borders(vtx_path, frg_path);

	material = Material(vec3(0.5f, 0.4f, 0.3f), vec3(0.4f, 0.8f, 0.2f), vec3(0.8f), 100.0f);

	friction = 0.08f;

	init_gl();
}

Tile::~Tile()
{
	for (vector<Border*>::size_type i = 0; i < borders.size(); ++i) {
		delete borders[i];
	}
}

void Tile::init_borders(char *vtx_path, char *frg_path)
{
	vector<vec3> edges;

	for (int i = 0; i < edge_count; ++i) {
		if (!neighbors[i]) {
			if (i == edge_count - 1) {
				edges.push_back(vertices.at(i));
				edges.push_back(vertices.at(0));
			}
			else {
				edges.push_back(vertices.at(i));
				edges.push_back(vertices.at(i+1));
			}
		}
	}

	for (vector<Border*>::size_type i = 0; i < edges.size(); i += 2) {
		vector<vec3> edges_for_border;
		edges_for_border.push_back(edges[i]);
		edges_for_border.push_back(edges[i + 1]);
		borders.push_back(new Border(tile_id, edges_for_border, vtx_path, frg_path));
	}
}

void Tile::draw(Camera *camera, Light *light)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	shader->use();

	glBindVertexArray(vao_handle);

	Shader::set_uniforms_camera(shader, camera, mat4(1.0f));
	Shader::set_uniforms_light(shader, camera, light);
	Shader::set_uniforms_material(shader, material);

	glDrawArrays(GL_POLYGON, 0, vertices.size());

	glBindVertexArray(0);

	glDisable(GL_CULL_FACE);

	for (vector<Border*>::size_type i = 0; i < borders.size(); ++i) {
		borders[i]->draw(camera, light);
	}
}

void Tile::init_gl()
{
	vector<float> vertex_indices;

	for (vector<vec3>::size_type i = 0; i < vertices.size(); ++i) {
		vertex_indices.push_back(vertices[i].x);
		vertex_indices.push_back(vertices[i].y);
		vertex_indices.push_back(vertices[i].z);
	}

	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);

	unsigned int handle[2];
	glGenBuffers(2, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex_indices.size() * sizeof(float), &vertex_indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	float n[3] = { normal.x, normal.y, normal.z };
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), n, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

float Tile::get_friction()
{
	return friction;
}

vector<Border*> Tile::get_borders()
{
	return borders;
}

vector<int> Tile::get_neighbors()
{
	return neighbors;
}