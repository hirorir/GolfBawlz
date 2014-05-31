#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <iostream>
#include <vector>
#include <gl\glew.h>
#include <gl\freeglut.h>

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#include "Object.h"
#include "Light.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"

using namespace std;
using namespace glm;

class Object3D : public Object
{
public:
	Object3D();

	Object3D(int id, vec3 position);

	~Object3D();

	virtual void draw(Camera *camera, Light *light) = 0;

	int get_tile_id() const;

	void set_tile_id(int id);

	Material *get_material() const;

	void set_material(Material *mat);

protected:
	Shader *shader;
	Material *material;
	GLuint vao_handle;
	int tile_id;
};

#endif