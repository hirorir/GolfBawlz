#include "Camera.h"

using namespace glm;
using namespace std;

vector<Camera*> Camera::activeCameras;

void Camera::addCamera(Camera& cam){
	activeCameras.push_back(&cam);
}	//adds the camera to the list of "active" cameras

void Camera::update(){
	view = lookAt(eye, center, up);
}	//update the frame using this camera

void Camera::translate(float x, float y, float z){
	eye += vec3(x, y, z);
}	//translate the camera in world units

void Camera::rotate(float x, float y, float z){

}	//rotate the camera in degrees around the x, y, or z axis

void Camera::removeCamera(Camera& cam){

}	//removes the camera to the list of "active" cameras

void Camera::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	projection = perspective(70.0f, (float)w / h, 0.3f, 100.0f);
}

Camera& Camera::operator[](int index){		//can't make operator functions static... has to be called from an instance
	if (index <= activeCameras.size())
		return *(activeCameras[index]);
	else{
		cout << "ERROR: Camera " + index << " doesn't exist!" << endl;
		exit(0);
	}
}

Camera::Camera(){
	eye = vec3(0, 2, 2);
	center = vec3(0, 0, 0);
	up = vec3(0, 1, 0);
	model = mat4(1.0f);
	addCamera(*this);
}	//default constructor

Camera::Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ){
	eye.x = eyeX;	eye.y = eyeY;	eye.z = eyeZ;
	center.x = centerX;	center.y = centerY;	center.z = centerZ;
	up.x = upX; up.y = upY; up.z = upZ;
	model = mat4(1.0f);
	addCamera(*this);
}	//construct using floats

Camera::Camera(vec3 eye, vec3 center, vec3 up){
	this->eye = eye;
	this->center = center;
	this->up = up;
	model = mat4(1.0f);
	addCamera(*this);
}	//construct using vecs

Camera::~Camera(){

}