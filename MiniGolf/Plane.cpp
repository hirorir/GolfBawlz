#include "Plane.h"

Plane::Plane() {}

Plane::Plane(int id, vec3 position, vector<vec3> verts) : Object3D(id, position)
{
	vertices = verts;

	normal = calculate_normal();

	calc_min_max();

	dist_from_origin = -dot(normal, vertices[0]);

	init_gl();
}

Plane::Plane(int id, vec3 position) : Object3D(id, position) {}

void Plane::calc_min_max()
{
	min_vec = max_vec = vertices[0];
	for (vector<vec3>::size_type i = 0; i < vertices.size(); ++i) {
		vec3 v = vertices[i];

		if (v.x < min_vec.x) {
			min_vec.x = v.x;
		}
		else if (v.x > max_vec.x) {
			max_vec.x = v.x;
		}

		if (v.y < min_vec.y) {
			min_vec.y = v.y;
		}
		else if (v.y > max_vec.y) {
			max_vec.y = v.y;
		}

		if (v.z < min_vec.z) {
			min_vec.z = v.z;
		}
		else if (v.z > max_vec.z) {
			max_vec.z = v.z;
		}
	}

	if (min_vec.y == max_vec.y) {
		direction_gravity = vec3(0.0f);
		is_sloped = false;
	}
	else {
		direction_gravity = PhysicsObject::plane_gravity_direction(normal);
		is_sloped = true;
	}
}

bool Plane::point_in_plane(vec3 point)
{
	if (point.x < min_vec.x  || point.z < min_vec.z || point.x > max_vec.x || point.z > max_vec.z) {
		return false;
	}
	return true;
}

void Plane::draw(Camera *camera, Light *light)
{
	shader->use();

	glBindVertexArray(vao_handle);

	shader->set_uniforms(camera, light, material, mat4(1.0f));

	glDrawArrays(GL_POLYGON, 0, vertices.size());

	glBindVertexArray(0);
}

void Plane::init_gl()
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

vector<vec3> Plane::get_vertices()
{
	return vertices;
}

vec3 Plane::get_normal()
{
	return normal;
}

bool Plane::sloped()
{
	return is_sloped;
}

float Plane::get_dist_from_origin()
{
	return dist_from_origin;
}

vec3 Plane::calculate_normal()
{
	if (vertices.size() < 3) {
		cout << "error - not enough vertices in this Plane to calculate the normals." << endl;
		return vec3(0.0f, 1.0f, 0.0f); // Just assume 'up' vector if we have an error.
	}
	vec3 v1 = vertices[0], v2 = vertices[1], v3 = vertices[2];

	vec3 a = v2 - v1;
	vec3 b = v3 - v1;

	return normalize(cross(a, b));
}

vec3 Plane::get_direction_gravity()
{
	return direction_gravity;
}