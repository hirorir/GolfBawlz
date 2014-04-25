#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <iostream>
#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>

#include <glm\glm.hpp>

#include "Shader.h"
#include "Material.h"

using namespace std;
using namespace glm;

class Object3D
{
public:
	Object3D();

	Object3D(int tile_id, vec3 position);

	virtual void init_gl();

	virtual void draw(Shader *shader);

	virtual void set_shader_uniforms(Shader *shader, Material mat);

	void print();

	GLuint get_vao_handle();

	int get_tile_id();

	void set_tile_id(int id);

	vec3 get_position();

	void set_position(vec3 position);

protected:
	GLuint vao_handle;
	int tile_id;
	vec3 position;
	vector<float> circle_vertices;
};

#endif