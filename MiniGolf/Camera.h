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
	Camera();										//default constructor

	Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

	Camera(vec3 eye, vec3 center, vec3 up);	

	~Camera();										//default destructor

	Camera& operator[](int index);					//retrieve camera at index from activeCameras

	static void addCamera(Camera& cam);				//adds the camera to the list of "active" cameras

	void translate(float x, float y, float z);		//translate the camera in world units

	void translate(vec3 v);

	void rotate(float h, float v);					//rotate the camera in degrees around horizontal or vertical

	void removeCamera(Camera& cam);					//removes the camera to the list of "active" cameras

	void reset_model();                             //resets world space.

	mat4 get_view();                                //returns the view matrix.

	void change_view(mat4 transform);               //transform the view.

	friend class GameManager;

	friend class Level;

	friend class Shader;

	static float dx;

	static float dy;

private:
	mat4 model;
	mat4 view;
	mat4 projection;
	vec3 eye, center, up;
	float hRadians, vRadians;
	static vector<Camera*> activeCameras;			//singleton handler of the cameras that are active

	void resize(int w, int h);
	void update();									//update the frame using this camera
};

#endif