#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <iostream>
#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Light.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"

using namespace std;
using namespace glm;

class Object3D
{
public:
	Object3D();

	Object3D(int tile_id, vec3 position);

	~Object3D();

	virtual void draw(Camera *camera, Light *light) = 0;

	void print();

	int get_tile_id();

	void set_tile_id(int id);

	vec3 get_position();

	void set_position(vec3 position);

	void set_x(float x);

	void set_y(float y);

	void set_z(float z);

	mat4 get_model_to_world();

	void set_model_to_world(mat4 mtw);

protected:
	Shader *shader;
	GLuint vao_handle;
	int tile_id;
	vec3 position;
	mat4 model_to_world;
};

#endif