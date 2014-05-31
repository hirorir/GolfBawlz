#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <glm\glm.hpp>
#include <iostream>

#define GLM_FORCE_RADIANS

#include <glm\gtx\transform.hpp>
#include <gl/freeglut.h>
#include <gl/GLU.h>
#include <math.h>

using namespace std;
using namespace glm;

class Camera
{
public:
	Camera(); //default constructor

	void resize(int w, int h);

	mat4 get_view() const; //returns the view matrix.

	mat4 get_projection() const; //returns the projection matrix;

	void change_view(mat4 transform); //transform the view.

private:
	mat4 view;
	mat4 projection;
	vec3 eye, center, up;
};

#endif