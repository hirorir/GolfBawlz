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

	Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

	Camera(vec3 eye, vec3 center, vec3 up);	

	Camera& operator[](int index); //retrieve camera at index from activeCameras

	static void addCamera(Camera& cam); //adds the camera to the list of "active" cameras

	void removeCamera(Camera& cam); //removes the camera to the list of "active" cameras

	mat4 get_view(); //returns the view matrix.

	mat4 get_projection(); //returns the projection matrix;

	void set_view(mat4 transform); //transform the view.

	void resize(int w, int h);

	friend class GameManager;

	friend class Level;

	friend class Shader;

private:
	mat4 view;
	mat4 projection;
	vec3 eye, center, up;

	static vector<Camera*> activeCameras; //singleton handler of the cameras that are active
};

#endif