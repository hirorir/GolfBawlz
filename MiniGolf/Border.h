#ifndef BORDER_H
#define BORDER_H

#include "Object3D.h"
#include "Plane.h"

class Border : public Object3D, public Plane
{
public:
	Border(int id, vector<vec3> e, char *vtx_path, char *frg_path);

	virtual void draw(Camera *camera, Light *light);

	void print();

private:
	vector<float> edge_indices;

	void init_gl();

	void adjust_edges();
};

#endif