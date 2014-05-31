#include "Light.h"

Light::Light() {}

Light::Light(vec4 p, vec3 a, vec3 d, vec3 s)
{
	position = p;
	ambient = a;
	diffuse = d;
	specular = s;
}

vec4 Light::get_position() const
{
	return position;
}

vec3 Light::get_ambient() const
{
	return ambient;
}

vec3 Light::get_diffuse() const
{
	return diffuse;
}

vec3 Light::get_specular() const
{
	return specular;
}