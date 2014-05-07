#include "Object3D.h"

Object3D::Object3D() {}

Object3D::Object3D(int tile_id, vec3 position)
{
	this->tile_id = tile_id;
	this->position = position;
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

void Object3D::set_position(vec3 position)
{
	this->position = position;
}

mat4 Object3D::get_model_to_world()
{
	return model_to_world;
}

void Object3D::set_model_to_world(mat4 mtw)
{
	model_to_world = mtw;
}