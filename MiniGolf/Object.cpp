#include "Object.h"

Object::Object() {}

Object::Object(vec3 pos) 
{
	position = pos;
	model_to_world = mat4(1.0f);
}

vec3 Object::get_position() const
{
	return position;
}

void Object::set_position(vec3 position)
{
	this->position = position;
	model_to_world *= translate(position);
}

mat4 Object::get_model_to_world() const
{
	return model_to_world;
}

void Object::set_model_to_world(mat4 mtw)
{
	model_to_world = mtw;
}