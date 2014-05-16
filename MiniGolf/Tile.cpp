#include "Tile.h"

Tile::Tile() {}

Tile::Tile(int id, int ecount, vector<float> verts, vector<int> nbors, char *vtx_path, char *frg_path) : Object3D(id, vtx_path, frg_path), Plane(verts)
{
	num_edge_indices = ecount;
	vertex_indices = verts;
	neighbors = nbors;

	edge_indices = calculate_edges();

	init_borders(vtx_path, frg_path);
	
	position = vec3(vertex_indices[0], vertex_indices[1], vertex_indices[2]);

	material = Material(vec3(0.5f, 0.4f, 0.3f), vec3(0.4f, 0.8f, 0.2f), vec3(0.8f), 100.0f);

	friction = 0.4f;

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
	if (edge_indices.size()) {

		vector<vec3> edges;

		for (vector<float>::size_type i = 0; i < edge_indices.size(); i += 3) {
			edges.push_back(vec3(edge_indices[i], edge_indices[i + 1], edge_indices[i + 2]));
		}

		for (vector<Border*>::size_type i = 0; i < edges.size(); i += 2) {
			vector<vec3> edges_for_border;
			edges_for_border.push_back(edges[i]);
			edges_for_border.push_back(edges[i + 1]);
			borders.push_back(new Border(tile_id, edges_for_border, vtx_path, frg_path));
		}
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

vector<float> Tile::calculate_edges()
{
	int vertex_index = 0;
	vector<float> edges;

	for (int e = 0; e < num_edge_indices; ++e) {
		if (neighbors[e] == 0) {
			if (vertex_index == vertex_indices.size() - 3) {
				int i;

				for (i = vertex_index; i < vertex_indices.size(); ++i) {
					edges.push_back(vertex_indices[i]);
				}

				for (i = 0; i < 3; ++i) {
					edges.push_back(vertex_indices[i]);
				}
			}
			else {
				for (int i = vertex_index; i < vertex_index + 6; ++i) {
					edges.push_back(vertex_indices[i]);
				}
			}
		}

		vertex_index += 3;
	}

	return edges;
}

void Tile::init_gl()
{
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

void Tile::print()
{
	cout << "TILE (ID: " << tile_id << "): ";
	cout << "# total position indices: " << vertex_indices.size() << ", ";
	cout << "# total edge indices: " << num_edge_indices << endl;
	cout << "Vertex indices: (   ";
	for (int i = 0; i < vertex_indices.size(); ++i) {
		cout << vertex_indices[i] << "   ";
	}
	cout << ")" << endl;
	cout << "Edge indices (Size = " << edge_indices.size() << "): (   ";
	for (vector<float>::size_type i = 0; i < edge_indices.size(); ++i) {
		cout << edge_indices[i] << "   ";
	}
	cout << ")" << endl;
	cout << "Neighbor IDs: ";
	for (int i = 0; i < num_edge_indices; ++i) {
		if (i == num_edge_indices - 1) {
			cout << neighbors[i];
		}
		else {
			cout << neighbors[i] << ", ";
		}
	}
	cout << endl << endl;
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