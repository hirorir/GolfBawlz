#include "Camera.h"

Camera::Camera()
{
	eye = vec3(0.1f, 6.0f, 0.1f);
	center = vec3(0.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	view = lookAt(eye, center, up);
}

void Camera::resize(int w, int h)
{
	glViewport(0, 0, w, h);
	projection = perspective(70.0f, (float)w / h, 0.3f, 100.0f);
}

mat4 Camera::get_view() const
{
	return view;
}

mat4 Camera::get_projection() const
{
	return projection;
}

void Camera::change_view(mat4 transform)
{
	view *= transform;
}