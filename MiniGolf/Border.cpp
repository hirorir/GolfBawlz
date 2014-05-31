#include "Border.h"

Border::Border(int id, vector<vec3> e) : Plane(id, e[0], e)
{
	material = new Material(vec3(1.0f, 0.1f, 0.1f), vec3(0.9f, 0.1f, 0.1f), vec3(0.0f), 100.0f);

	vector<vec3> new_edges;
	for (vector<vec3>::size_type i = 0; i < e.size(); i += 2) {
		vec3 first_vertex = vertices[i];
		vec3 second_vertex = vertices[i + 1];

		new_edges.push_back(first_vertex);
		new_edges.push_back(second_vertex);
		new_edges.push_back(vec3(second_vertex.x, second_vertex.y + 0.2f, second_vertex.z));
		new_edges.push_back(vec3(first_vertex.x, first_vertex.y + 0.2f, first_vertex.z));
	}

	vertices = new_edges;

	init_gl();
}

void Border::draw(Camera *camera, Light *light)
{
	shader->use();

	glBindVertexArray(vao_handle);

	shader->set_uniforms(camera, light, material, mat4(1.0f));

	glDrawArrays(GL_QUADS, 0, vertices.size());

	glBindVertexArray(0);
}

void Border::init_gl()
{
	vector<float> edge_indices;
	for (vector<vec3>::size_type i = 0; i < vertices.size(); ++i) {
		edge_indices.push_back(vertices[i].x);
		edge_indices.push_back(vertices[i].y);
		edge_indices.push_back(vertices[i].z);
	}

	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);

	unsigned int handle[1];
	glGenBuffers(1, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, edge_indices.size() * sizeof(float), &edge_indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}