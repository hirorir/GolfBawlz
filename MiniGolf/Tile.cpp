#include "Tile.h"

Tile::Tile(int id, int vcount, int ecount, vector<float> verts, vector<int> nbors)
{
	tile_id = id;
	vertex_count = vcount;
	edge_count = ecount;
	vertices = verts;
	neighbors = nbors;
	normal = calculate_normal();
	material = Material(vec3(0.5f, 0.4f, 0.3f), vec3(0.5f, 0.9f, 0.3f), vec3(0.8f), 100.0f);
	edges = calculate_edges();

	init_gl_tile();

	if (edges.size() > 0) {
		init_gl_border();
	}
}

void Tile::draw(Shader *shader)
{
	draw_tile(shader);

	if (edges.size() > 0) {
		draw_border(shader);
	}
}

void Tile::draw_tile(Shader *shader)
{
	glBindVertexArray(tile_vao);

	set_shader_uniforms(shader, material);
	glDrawArrays(GL_POLYGON, 0, vertex_count);

	glBindVertexArray(0);
}

void Tile::draw_border(Shader *shader)
{
	glBindVertexArray(border_vao);

	material = Material(vec3(1.0f, 0.1f, 0.1f), vec3(0.9f, 0.1f, 0.1f), vec3(0.0f), 100.0f);
	set_shader_uniforms(shader, material);
	glDrawArrays(GL_LINES, 0, edges.size());

	glBindVertexArray(0);
}

void Tile::set_shader_uniforms(Shader *shader, Material mat)
{
	shader->setUniform("Material.Ka", mat.get_ambient());
	shader->setUniform("Material.Kd", mat.get_diffuse());
	shader->setUniform("Material.Ks", mat.get_specular());
	shader->setUniform("Material.Shininess", mat.get_shininess());
}

vector<float> Tile::calculate_edges()
{
	int vertex_index = 0;
	vector<float> edges;

	for (int e = 0; e < edge_count; ++e) {
		if (neighbors[e] == 0) {
			if (vertex_index == vertex_count - 3) {
				int i;

				for (i = vertex_index; i < vertex_count; ++i) {
					edges.push_back(vertices[i]);
				}

				for (i = 0; i < 3; ++i) {
					edges.push_back(vertices[i]);
				}
			}
			else {
				for (int i = vertex_index; i < vertex_index + 6; ++i) {
					edges.push_back(vertices[i]);
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

	if (vertex_count >= 9) {
		vec3 v1(vertices[0], vertices[1], vertices[2]);

		vec3 v2(vertices[3], vertices[4], vertices[5]);

		vec3 v3(vertices[6], vertices[7], vertices[8]);

		a = v1 - v2;
		b = v1 - v3;
	}
	else {
		cout << "error - not enough vertices in this Tile to calculate the normals." << endl;
	}

	return cross(a, b);
}

void Tile::init_gl_tile()
{
	glGenVertexArrays(1, &tile_vao);
	glBindVertexArray(tile_vao);

	unsigned int handle[2];
	glGenBuffers(2, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	float n[3] = { normal.x, normal.y, normal.z };
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), n, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(1);
}

void Tile::init_gl_border()
{
	glLineWidth(8.0f);

	glGenVertexArrays(1, &border_vao);
	glBindVertexArray(border_vao);

	unsigned int handle[1];
	glGenBuffers(1, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, edges.size() * sizeof(float), &edges[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(0);
}

void Tile::print()
{
	cout << "TILE (ID: " << tile_id << "): ";
	cout << "# vertex indicies: " << vertex_count << ", ";
	cout << "# edges: " << edge_count << endl;
	cout << "Vertex indicies: (   ";
	for (int i = 0; i < vertex_count; ++i) {
			cout << vertices[i] << "   ";
	}
	cout << ")" << endl;
	cout << "Edge indicies (Size = " << edges.size() << "): (   ";
	for (vector<float>::size_type i = 0; i < edges.size(); ++i) {
		cout << edges[i] << "   ";
	}
	cout << ")" << endl;
	cout << "Neighbor IDs: ";
	for (int i = 0; i < edge_count; ++i) {
		if (i == edge_count - 1) {
			cout << neighbors[i];
		}
		else {
			cout << neighbors[i] << ", ";
		}
	}
	cout << endl << endl;
}

int Tile::get_tile_id()
{
	return tile_id;
}

int Tile::get_vertex_count()
{
	return vertex_count;
}

int Tile::get_edge_count()
{
	return edge_count;
}

vector<float> Tile::get_verticies()
{
	return vertices;
}

vector<int> Tile::get_neighbors()
{
	return neighbors;
}

vec3 Tile::get_normal()
{
	return normal;
}

Material Tile::get_material()
{
	return material;
}

void Tile::set_material(Material mat)
{
	material = mat;
}