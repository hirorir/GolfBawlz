#ifndef LIGHT_H
#define LIGHT_H

#include <glm\glm.hpp>

using namespace glm;

class Light
{
public:
	Light();

	Light(vec4 p, vec3 a, vec3 d, vec3 s);

	vec4 get_position() const;

	vec3 get_ambient() const;

	vec3 get_diffuse() const;

	vec3 get_specular() const;

private:
	vec4 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#endif