#include "Object3D.h"

Object3D::Object3D() {}

Object3D::Object3D(int id, vec3 pos) : Object(pos)
{
	shader = new Shader("shaders/ads.vert", "shaders/ads.frag");
	shader->readAndCompileShader();

	tile_id = id;
}

Object3D::~Object3D()
{
	delete shader;
	delete material;
}

int Object3D::get_tile_id() const
{
	return tile_id;
}

void Object3D::set_tile_id(int id)
{
	tile_id = id;
}

Material *Object3D::get_material() const
{
	return material;
}

void Object3D::set_material(Material *mat)
{
	material = mat;
}