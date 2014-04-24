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

	init_gl();
}

void Tile::draw()
{
	glBindVertexArray(vao_handle);
	glDrawArrays(GL_POLYGON, 0, vertex_count);
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

void Tile::init_gl()
{
	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);

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

void Tile::print()
{
	cout << endl;
	cout << "TILE (ID: " << tile_id << "): ";
	cout << "# verticies: " << vertex_count << ", ";
	cout << "# edgess: " << edge_count << endl;
	cout << "Verticies: (";
	for (int i = 0; i < vertex_count; ++i) {
		if (i == vertex_count - 1) {
			cout << vertices[i];
		}
		else {
			cout << vertices[i] << ", ";
		}
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