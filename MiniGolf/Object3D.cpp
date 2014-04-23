#include "Object3D.h"

Object3D::Object3D()
{

}

Object3D::Object3D(vector<float> position, int tile_id)
{
	this->position = position;
	this->tile_id = tile_id;
}

void Object3D::print()
{
	cout << endl << "Object3D (Tile ID: " << tile_id << ")" << endl;
	cout << "Position: (" << position[0] << ", " << position[1] << ", " << position[2] << ")" << endl << endl;
}

GLuint Object3D::get_vao_handle()
{
	return vao_handle;
}

int Object3D::get_tile_id()
{
	return tile_id;
}

void Object3D::set_tile_id(int id)
{
	tile_id = id;
}

vector<float> Object3D::get_position()
{
	return position;
}

void Object3D::set_position(vector<float> position)
{
	this->position = position;
}