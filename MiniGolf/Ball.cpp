#include "Ball.h"

Ball::Ball() {}

Ball::Ball(int tile_id, vec3 pos, char *vtx_path, char *frg_path) : Object3D(tile_id, pos, vtx_path, frg_path)
{
	radius = 0.1f;
	slices = 40;
	stacks = 40;

	material = Material(vec3(0.0f, 0.1f, 1.0f), vec3(0.4f, 0.1f, 0.0f), vec3(0.0f), 100.0f);

	model_to_world = translate(vec3(position.x, position.y + 0.1, position.z));

	this->init_gl();
}

void Ball::run_simulation()
{
	double time_now = timer.get_elapsed_time_in_sec();
	double time_elapsed = time_now - last_time;
	last_time = time_now;

	while (!forces.empty()) {
		velocity += forces.front(); // Apply all forces.
		forces.pop();
	}

	if (t->sloped() || dot(velocity, velocity) >= t->get_friction()) {
		velocity += t->get_direction_gravity();

		velocity += PhysicsObject::friction(velocity, t->get_friction());

		if (!collide_with_edge(time_elapsed)) {
			position = PhysicsObject::euler_integration(position, velocity, time_elapsed);
		}

		position.y = (-t->get_dist_from_origin() - position.x * t->get_normal().x - position.z * t->get_normal().z) / t->get_normal().y;
	}
	else {
		velocity = vec3(0.0f);
	}

	model_to_world = translate(vec3(position.x, position.y + 0.1, position.z));
}

bool Ball::collide_with_edge(double time_elapsed)
{
	vector<Border*> borders = t->get_borders();

	if (borders.size()) {
		bool collision_handled = false;

		for (vector<Border*>::size_type i = 0; i < borders.size(); ++i) {
			float time_of_collide = -(dot(borders[i]->get_normal(), position) + borders[i]->get_dist_from_origin()) / dot(velocity, borders[i]->get_normal());

			if (time_of_collide >= 0 && time_of_collide <= time_elapsed) {
				vec3 collision_position = PhysicsObject::euler_integration(position, velocity, time_of_collide);

				position = collision_position;

				velocity = PhysicsObject::plane_reflection_velocity(velocity, borders[i]->get_normal());

				double time_remaining = time_elapsed - time_of_collide;

				position = PhysicsObject::euler_integration(position, velocity, time_remaining);

				collision_handled = true;
			}
		}

		return collision_handled;
	}
	return false;
}

void Ball::draw(Camera *camera, Light *light)
{
	shader->use();

	glBindVertexArray(vao_handle);

	Shader::set_uniforms_camera(shader, camera, model_to_world);
	Shader::set_uniforms_light(shader, camera, light);
	Shader::set_uniforms_material(shader, material);

	glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));

	glBindVertexArray(0);
}

void Ball::init_gl()
{
	nVerts = (GLuint) (slices + 1) * (GLuint) (stacks + 1);
	elements = (GLuint) (slices * 2 * (GLuint) (stacks - 1)) * 3;

	// Verts
	float * v = new float[3 * nVerts];
	// Normals
	float * n = new float[3 * nVerts];
	// Tex coords
	float * tex = new float[2 * nVerts];
	// Elements
	unsigned int * el = new unsigned int[elements];

	// Generate the vertex data
	generate_verts(v, n, tex, el);

	// Create and populate the buffer objects
	unsigned int handle_ball[4];
	glGenBuffers(4, handle_ball);

	glBindBuffer(GL_ARRAY_BUFFER, handle_ball[0]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), v, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle_ball[1]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), n, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle_ball[2]);
	glBufferData(GL_ARRAY_BUFFER, (2 * nVerts) * sizeof(float), tex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_ball[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(unsigned int), el, GL_STATIC_DRAW);

	delete[] v;
	delete[] n;
	delete[] el;
	delete[] tex;

	// Create the VAO
	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);

	glEnableVertexAttribArray(0);  // Vertex position
	glBindBuffer(GL_ARRAY_BUFFER, handle_ball[0]);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);  // Vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, handle_ball[1]);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, handle_ball[2]);
	glEnableVertexAttribArray(2);  // Texture coords
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle_ball[3]);

	glBindVertexArray(0);
}

void Ball::generate_verts(float * verts, float * norms, float * tex, unsigned int * el)
{
	// Generate positions and normals
	GLfloat theta, phi;
	GLfloat thetaFac = (GLfloat) (2.0 * PI) / slices;
	GLfloat phiFac = (GLfloat) PI / stacks;
	GLfloat nx, ny, nz, s, t;
	GLuint idx = 0, tIdx = 0;
	for (int i = 0; i <= slices; i++) {
		theta = i * thetaFac;
		s = (GLfloat)i / slices;
		for (int j = 0; j <= stacks; j++) {
			phi = j * phiFac;
			t = (GLfloat)j / stacks;
			nx = sinf(phi) * cosf(theta);
			ny = sinf(phi) * sinf(theta);
			nz = cosf(phi);
			verts[idx] = radius * nx; verts[idx + 1] = radius * ny; verts[idx + 2] = radius * nz;
			norms[idx] = nx; norms[idx + 1] = ny; norms[idx + 2] = nz;
			idx += 3;

			tex[tIdx] = s;
			tex[tIdx + 1] = t;
			tIdx += 2;
		}
	}

	// Generate the element list
	idx = 0;
	for (int i = 0; i < slices; i++) {
		GLuint stackStart = i * (GLuint) (stacks + 1);
		GLuint nextStackStart = (i + 1) * (GLuint) (stacks + 1);
		for (int j = 0; j < stacks; j++) {
			if (j == 0) {
				el[idx] = stackStart;
				el[idx + 1] = stackStart + 1;
				el[idx + 2] = nextStackStart + 1;
				idx += 3;
			}
			else if (j == stacks - 1) {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j;
				idx += 3;
			}
			else {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j + 1;
				el[idx + 3] = nextStackStart + j;
				el[idx + 4] = stackStart + j;
				el[idx + 5] = nextStackStart + j + 1;
				idx += 6;
			}
		}
	}
}

float Ball::get_radius()
{
	return radius;
}

void Ball::set_current_tile(Tile *tile)
{
	tile_id = tile->get_tile_id();
	t = tile;
	//cout << "current id = " << tile_id << endl;
}