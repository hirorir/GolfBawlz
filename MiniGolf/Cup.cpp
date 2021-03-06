#include "Cup.h"

Cup::Cup() {}

Cup::Cup(int tile_id, vec3 position) : Object3D(tile_id, position)
{
	model_to_world = translate(vec3(position.x, position.y - 0.09, position.z)) * scale(vec3(0.2f));

	material = new Material(vec3(0.1f, 0.1f, 0.1f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f), 100.0f);

	isect_sphere = new Ball(tile_id, position);
	isect_sphere->set_radius(0.1f);

	this->init_gl();
}

Cup::~Cup()
{
	delete isect_sphere;
}

Ball *Cup::get_sphere() const
{
	return isect_sphere;
}

void Cup::init_gl()
{
	float side = 1.0f;
	float side2 = side / 2.0f;

	float v[24 * 3] = {
		// Front
		-side2, -side2, side2,
		side2, -side2, side2,
		side2, side2, side2,
		-side2, side2, side2,
		// Right
		side2, -side2, side2,
		side2, -side2, -side2,
		side2, side2, -side2,
		side2, side2, side2,
		// Back
		-side2, -side2, -side2,
		-side2, side2, -side2,
		side2, side2, -side2,
		side2, -side2, -side2,
		// Left
		-side2, -side2, side2,
		-side2, side2, side2,
		-side2, side2, -side2,
		-side2, -side2, -side2,
		// Bottom
		-side2, -side2, side2,
		-side2, -side2, -side2,
		side2, -side2, -side2,
		side2, -side2, side2,
		// Top
		-side2, side2, side2,
		side2, side2, side2,
		side2, side2, -side2,
		-side2, side2, -side2
	};

	float n[24 * 3] = {
		// Front
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		// Right
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		// Back
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		// Left
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		// Bottom
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		// Top
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	float tex[24 * 2] = {
		// Front
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Right
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Back
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Left
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Bottom
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		// Top
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	GLuint el[] = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);

	unsigned int handle_cup[4];
	glGenBuffers(4, handle_cup);

	glBindBuffer(GL_ARRAY_BUFFER, handle_cup[0]);
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), v, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(0);  // Vertex position

	glBindBuffer(GL_ARRAY_BUFFER, handle_cup[1]);
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), n, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(1);  // Vertex normal

	glBindBuffer(GL_ARRAY_BUFFER, handle_cup[2]);
	glBufferData(GL_ARRAY_BUFFER, 24 * 2 * sizeof(float), tex, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, ((GLubyte *)NULL + (0)));
	glEnableVertexAttribArray(2);  // texture coords

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_cup[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(GLuint), el, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Cup::draw(Camera *camera, Light *light)
{
	shader->use();

	glBindVertexArray(vao_handle);

	shader->set_uniforms(camera, light, material, model_to_world);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));

	glBindVertexArray(0);
}