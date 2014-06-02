#ifndef TEE_H
#define TEE_H

#include "Plane.h"

class Tee : public Plane {
public:
	Tee();

	Tee(int id, vec3 position, vector<vec3> verts);
};

#endif