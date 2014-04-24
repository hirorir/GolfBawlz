#ifndef CAMERA_H
#define CAMERA_H
#include <vector>
#include <glm\glm.hpp>
#include <iostream>
#include <glm\gtx\transform.hpp>
#include <gl/freeglut.h>
#include <gl/GLU.h>

using namespace std;
using namespace glm;

class GameManager;

class Camera
{
private:
	mat4 model;
	mat4 view;
	mat4 projection;
	vec3 eye, center, up;
	static vector<Camera*> activeCameras;			//singleton handler of the cameras that are active
	void resize(int w, int h);
	void update();									//update the frame using this camera
public:
	Camera& operator[](int index);					//retrieve camera at index from activeCameras
	static void addCamera(Camera& cam);				//adds the camera to the list of "active" cameras
	void translate(float x, float y, float z);		//translate the camera in world units
	void translate(vec3 v);
	void rotate(float x, float y, float z);			//rotate the camera in degrees around the x, y, or z axis
	void removeCamera(Camera& cam);					//removes the camera to the list of "active" cameras

	Camera();										//default constructor
	Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
	Camera(vec3 eye, vec3 center, vec3 up);
	~Camera();										//default destructor

	friend class GameManager;
	friend class Shader;
};

#endif