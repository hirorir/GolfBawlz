#include "Camera.h"

using namespace glm;
using namespace std;

vector<Camera*> Camera::activeCameras;

Camera::Camera()
{
	eye = vec3(0, 5, 5);
	center = vec3(0, 0, 0);
	up = vec3(0, 1, 0);
	view = lookAt(eye, center, up);
	addCamera(*this);
	//default constructor
}

Camera::Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	eye.x = eyeX;	eye.y = eyeY;	eye.z = eyeZ;
	center.x = centerX;	center.y = centerY;	center.z = centerZ;
	up.x = upX; up.y = upY; up.z = upZ;
	addCamera(*this);
}	//construct using floats

Camera::Camera(vec3 eye, vec3 center, vec3 up)
{
	this->eye = eye;
	this->center = center;
	this->up = up;
	addCamera(*this);
}	//construct using vecs

void Camera::addCamera(Camera& cam)
{
	activeCameras.push_back(&cam);
}	//adds the camera to the list of "active" cameras

void Camera::removeCamera(Camera& cam)
{

}	//removes the camera to the list of "active" cameras

void Camera::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	projection = perspective(70.0f, (float)w / h, 0.3f, 100.0f);
}

Camera& Camera::operator[](int index)
{	//can't make operator functions static... has to be called from an instance
	if ((unsigned) index <= activeCameras.size()) {
		return *(activeCameras[index]);
	}
	else {
		cout << "ERROR: Camera " + index << " doesn't exist!" << endl;
		exit(0);
	}
}

mat4 Camera::get_view()
{
	return view;
}

mat4 Camera::get_projection()
{
	return projection;
}

void Camera::set_view(mat4 v)
{
	view = v;
}

void Camera::change_view(mat4 transform)
{
	view *= transform;
}