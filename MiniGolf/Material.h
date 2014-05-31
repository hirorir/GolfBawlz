#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm\glm.hpp>

using namespace glm;

class Material
{
public:
	Material();

	Material(vec3 a, vec3 d, vec3 s, float shine);

	vec3 get_ambient() const;

	vec3 get_diffuse() const;

	vec3 get_specular() const;

	float get_shininess() const;

private:
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

#endif