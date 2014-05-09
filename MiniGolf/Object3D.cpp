#include "Object3D.h"

Object3D::Object3D() {}

Object3D::Object3D(int id, vec3 pos, char *vtx_path, char *frg_path)
{
	shader = new Shader(vtx_path, frg_path);
	shader->readAndCompileShader();

	vao_handle = 0;
	tile_id = id;
	position = pos;
	model_to_world = mat4(1.0f);
}

Object3D::Object3D(int id, char *vtx_path, char *frg_path)
{
	shader = new Shader(vtx_path, frg_path);
	shader->readAndCompileShader();

	vao_handle = 0;
	tile_id = id;
	model_to_world = mat4(1.0f);
}

Object3D::~Object3D()
{
	delete shader;
}


void Object3D::print()
{
	cout << "Object3D (Tile ID: " << tile_id << ")" << endl;
	cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << endl << endl;
}

int Object3D::get_tile_id()
{
	return tile_id;
}

void Object3D::set_tile_id(int id)
{
	tile_id = id;
}

vec3 Object3D::get_position()
{
	return position;
}

void Object3D::set_position(vec3 position)		//the vec3 position is the amount it translates by, or the delta
{
	this->position = position;
	model_to_world *= translate(position);
}

mat4 Object3D::get_model_to_world()
{
	return model_to_world;
}

void Object3D::set_model_to_world(mat4 mtw)
{
	model_to_world = mtw;
}

void Object3D::set_x(float x)
{
	position.x += x;
	model_to_world *= translate(vec3(x, 0.0f, 0.0f));
}

void Object3D::set_y(float y)
{
	position.y += y;
	model_to_world *= translate(vec3(0.0f, y, 0.0f));
}

void Object3D::set_z(float z)
{
	position.z += z;
	model_to_world *= translate(vec3(0.0f, 0.0f, z));
}

void Object3D::new_shader(char *vtx_path, char *frg_path)
{
	shader->new_shader(vtx_path, frg_path);
}

Material Object3D::get_material()
{
	return material;
}

void Object3D::set_material(Material mat)
{
	material = mat;
}