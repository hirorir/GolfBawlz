#include "Camera.h"

using namespace glm;
using namespace std;

const double pi = 3.14159265358;

vector<Camera*> Camera::activeCameras;

float Camera::dx;
float Camera::dy;

Camera::Camera()
{
	eye = vec3(0, 3, 3);
	center = vec3(0, 0, 0);
	up = vec3(0, 1, 0);
	model = mat4(1.0f);
	hRadians = vRadians = dx = dy = 0;
	addCamera(*this);
}	//default constructor

Camera::Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	eye.x = eyeX;	eye.y = eyeY;	eye.z = eyeZ;
	center.x = centerX;	center.y = centerY;	center.z = centerZ;
	up.x = upX; up.y = upY; up.z = upZ;
	model = mat4(1.0f);
	hRadians = vRadians = dx = dy = 0;
	addCamera(*this);
}	//construct using floats

Camera::Camera(vec3 eye, vec3 center, vec3 up)
{
	this->eye = eye;
	this->center = center;
	this->up = up;
	model = mat4(1.0f);
	hRadians = vRadians = dx = dy = 0;
	addCamera(*this);
}	//construct using vecs

Camera::~Camera()
{

}

void Camera::addCamera(Camera& cam)
{
	activeCameras.push_back(&cam);
}	//adds the camera to the list of "active" cameras

void Camera::update()
{
	rotate(dx, dy);
	dx = dy = 0;
	view = lookAt(eye, center + eye, up);
}	//update the frame using this camera

void Camera::translate(float x, float y, float z)
{
	eye += vec3(x, y, z);
}	//translate the camera in world units

void Camera::translate(vec3 v)
{
	eye += v;
}

void Camera::rotate(float h, float v)	//h and v is the amount that a mouse translates along the x and y plane on the screen
{
	vRadians += v / 900 * pi;
	hRadians += h / 900 * pi;

	cout << vRadians << " " << hRadians << endl;

	center.x = cos(vRadians) * sin(hRadians);
	center.y = -sin(vRadians);
	center.z = cos(vRadians) * sin(hRadians);

	up.x = sin(vRadians) * sin(hRadians);
	up.y = cos(vRadians);
	up.z = sin(vRadians) * cos(hRadians);
}	//rotate the camera in degrees around the x, y, or z axis

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