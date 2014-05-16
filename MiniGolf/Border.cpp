#include "Border.h"

Border::Border(int id, vector<vec3> e, char *vtx_path, char *frg_path) : Object3D(id, vtx_path, frg_path)
{
	if (e.size()) {
		material = Material(vec3(1.0f, 0.1f, 0.1f), vec3(0.9f, 0.1f, 0.1f), vec3(0.0f), 100.0f);

		vertices = e;

		adjust_edges();

		normal = calculate_normal();

		dist_from_origin = -dot(normal, vertices[0]); 

		init_gl();
	}
}

void Border::adjust_edges()
{
	vector<vec3> new_edges;
	for (vector<vec3>::size_type i = 0; i < vertices.size(); i+=2) {
		vec3 first_vertex = vertices[i];
		vec3 second_vertex = vertices[i + 1];

		new_edges.push_back(first_vertex);
		new_edges.push_back(second_vertex);
		new_edges.push_back(vec3(second_vertex.x, second_vertex.y + 0.2f, second_vertex.z));
		new_edges.push_back(vec3(first_vertex.x, first_vertex.y + 0.2f, first_vertex.z));
	}

	vertices = new_edges;

	vector<float> new_edge_indices;
	for (vector<vec3>::size_type i = 0; i < vertices.size(); ++i) {
		new_edge_indices.push_back(vertices[i].x);
		new_edge_indices.push_back(vertices[i].y);
		new_edge_indices.push_back(vertices[i].z);
	}

	edge_indices = new_edge_indices;
}

void Border::draw(Camera *camera, Light *light)
{
	if (edge_indices.size() > 0) {
		glLineWidth(8.0f);

		shader->use();

		glBindVertexArray(vao_handle);

		Shader::set_uniforms_camera(shader, camera, mat4(1.0f));
		Shader::set_uniforms_light(shader, camera, light);
		Shader::set_uniforms_material(shader, material);

		glDrawArrays(GL_QUADS, 0, vertices.size());

		glBindVertexArray(0);
	}
}

void Border::init_gl()
{
	if (edge_indices.size() > 0) {
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
}

void Border::print()
{
	cout << "Number of Edge Vertices: " << vertices.size() << endl;
	cout << "Edges: " << endl;
	for (vector<vec3>::size_type i = 0; i < vertices.size(); ++i) {
		cout << "(" << vertices[i].x << ", " << vertices[i].y << ", " << vertices[i].z << " )" << endl;
	}
}