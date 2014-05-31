#ifndef OBJECT_H
#define OBJECT_H

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

using namespace std;
using namespace glm;

class Object
{
public:
	Object();

	Object(vec3 pos);

	vec3 get_position() const;

	void set_position(vec3 position);

	mat4 get_model_to_world() const;

	void set_model_to_world(mat4 mtw);

protected:
	vec3 position;
	mat4 model_to_world;
};

#endif