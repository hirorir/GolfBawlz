#include "Tile.h"

Tile::Tile(int id, int ecount, vector<float> verts, vector<int> nbors, char *vtx_path, char *frg_path) : Object3D(id, vtx_path, frg_path)
{
	num_edge_indices = ecount;
	vertex_indices = verts;
	neighbors = nbors;

	normal = calculate_normal();
	edge_indices = calculate_edges();

	position = vec3(vertex_indices[0], vertex_indices[1], vertex_indices[2]);

	init_gl_tile();
	init_gl_border();
}

void Tile::draw(Camera *camera, Light *light)
{
	shader->use();

	glBindVertexArray(tile_vao);

	material = Material(vec3(0.5f, 0.4f, 0.3f), vec3(0.4f, 0.8f, 0.2f), vec3(0.8f), 100.0f);

	Shader::set_uniforms_camera(shader, camera, mat4(1.0f));
	Shader::set_uniforms_light(shader, camera, light);
	Shader::set_uniforms_material(shader, material);

	glDrawArrays(GL_POLYGON, 0, vertex_indices.size() / 3);

	glBindVertexArray(0);

	if (edge_indices.size() > 0) {
		glBindVertexArray(border_vao);

		glLineWidth(8.0f);

		material = Material(vec3(1.0f, 0.1f, 0.1f), vec3(0.9f, 0.1f, 0.1f), vec3(0.0f), 100.0f);

		Shader::set_uniforms_material(shader, material);

		glDrawArrays(GL_LINES, 0, edge_indices.size());

		glBindVertexArray(0);
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

vec3 Tile::calculate_normal()
{
	vec3 a, b;

	if (vertex_indices.size() >= 9) {
		vec3 v1(vertex_indices[0], vertex_indices[1], vertex_indices[2]);

		vec3 v2(vertex_indices[3], vertex_indices[4], vertex_indices[5]);

		vec3 v3(vertex_indices[6], vertex_indices[7], vertex_indices[8]);

		a = v1 - v2;
		b = v1 - v3;
	}
	else {
		cout << "error - not enough vertices in this Tile to calculate the normals." << endl;
	}

	return normalize(cross(a, b));
}

void Tile::init_gl_tile()
{
	glGenVertexArrays(1, &tile_vao);
	glBindVertexArray(tile_vao);

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

void Tile::init_gl_border()
{
	if (edge_indices.size() > 0) {
		glGenVertexArrays(1, &border_vao);
		glBindVertexArray(border_vao);

		unsigned int handle[1];
		glGenBuffers(1, handle);

		glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
		glBufferData(GL_ARRAY_BUFFER, edge_indices.size() * sizeof(float), &edge_indices[0], GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}
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

int Tile::num_of_edge_indices()
{
	return num_edge_indices;
}

vector<float> Tile::get_vertices()
{
	return vertex_indices;
}

vector<int> Tile::get_neighbors()
{
	return neighbors;
}

vec3 Tile::get_normal()
{
	return normal;
}