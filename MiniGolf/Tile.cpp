#include "Tile.h"

Tile::Tile(int id, int vcount, int ecount, vector<float> verts, vector<int> nbors)
{
	tile_id = id;
	vertex_count = vcount;
	edge_count = ecount;
	vertices = verts;
	neighbors = nbors;
	normal = calculate_normal();

	init_gl();
}

void Tile::draw()
{
	glBindVertexArray(vao_handle);
	glDrawArrays(GL_POLYGON, 0, vertex_count);
}

vec3 Tile::calculate_normal()
{
	return vec3(0.0, 0.0, 0.0); // TO DO: Calculate tile normal, will be used for lighting.
}

void Tile::init_gl()
{
	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);

	unsigned int handle[1];
	glGenBuffers(1, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(0);
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