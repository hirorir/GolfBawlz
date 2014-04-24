#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm\glm.hpp>

using namespace glm;

class Material
{
public:
	Material();

	Material(vec3 a, vec3 d, vec3 s, float shine);

	vec4 get_position();

	vec3 get_ambient();

	vec3 get_diffuse();

	vec3 get_specular();

	float get_shininess();

private:
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

#endif