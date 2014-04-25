#include "Ball.h"

Ball::Ball()
{

}

void Ball::init_gl()
{
	radius = 0.2f;
	slices = 40;
	stacks = 40;

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
	unsigned int handle[4];
	glGenBuffers(4, handle);

	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), v, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glBufferData(GL_ARRAY_BUFFER, (3 * nVerts) * sizeof(float), n, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
	glBufferData(GL_ARRAY_BUFFER, (2 * nVerts) * sizeof(float), tex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(unsigned int), el, GL_STATIC_DRAW);

	delete[] v;
	delete[] n;
	delete[] el;
	delete[] tex;

	// Create the VAO
	glGenVertexArrays(1, &vao_handle);
	glBindVertexArray(vao_handle);

	glEnableVertexAttribArray(0);  // Vertex position
	glBindBuffer(GL_ARRAY_BUFFER, handle[0]);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);  // Vertex normal
	glBindBuffer(GL_ARRAY_BUFFER, handle[1]);
	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, handle[2]);
	glEnableVertexAttribArray(2);  // Texture coords
	glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[3]);

	glBindVertexArray(0);
}

void Ball::draw(Shader *shader)
{
	glBindVertexArray(vao_handle);
	set_shader_uniforms(shader, Material(vec3(0.0f, 0.1f, 1.0f), vec3(0.4f, 0.1f, 1.0f), vec3(0.0f), 100.0f));
	glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
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

void Ball::set_shader_uniforms(Shader *shader, Material mat)
{
	shader->setUniform("Material.Ka", mat.get_ambient());
	shader->setUniform("Material.Kd", mat.get_diffuse());
	shader->setUniform("Material.Ks", mat.get_specular());
	shader->setUniform("Material.Shininess", mat.get_shininess());
}