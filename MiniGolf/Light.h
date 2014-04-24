#ifndef LIGHT_H
#define LIGHT_H

#include <glm\glm.hpp>

using namespace glm;

class Light
{
public:
	Light();

	Light(vec4 p, vec3 a, vec3 d, vec3 s);

	vec4 get_position();

	vec3 get_ambient();

	vec3 get_diffuse();

	vec3 get_specular();

private:
	vec4 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#endif