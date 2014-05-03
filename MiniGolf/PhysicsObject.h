#ifndef PHYSICSOBJECTS_H
#define PHYSICSOBJECTS_H

#include <vector>
#include <gl\glew.h>
#include <glm\glm.hpp>

using namespace glm;
using namespace std;

class PhysicsObject{
private:
	vector<vec3> points;
	vector<vec3> polygons;

	PhysicsObject(vector<vec3> pts, vector<vec3> poly){
		points = pts;
		polygons = poly;
	}

	~PhysicsObject(){

	}
};

#endif