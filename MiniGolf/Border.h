#ifndef BORDER_H
#define BORDER_H

#include "Object3D.h"
#include "Plane.h"

class Border : public Plane
{
public:
	Border(int id, vector<vec3> e);

	virtual void draw(Camera *camera, Light *light);

private:
	void init_gl();
};

#endif