#include "Camera.h"

Camera::Camera()
{
	pos = vec3(0, 0, -3);
	pitch = 0.0f;
	yaw = 0.0f;
}

Camera::~Camera()
{
}

void Camera::turn(float dx, float dy)
{
	yaw += dx * .1;
	pitch += dy * .1;
}

vec3 Camera::getLocation()
{
	return pos;
}

void Camera::move(vec3 movement)
{
	pos += movement;
}

vec3 Camera::getForward()
{
	float x = cos(pitch) * sin(yaw);
	float y = sin(pitch);
	float z = cos(pitch) * cos(yaw);
	return vec3(x, y, z);
}

vec3 Camera::getLookAt()
{
	return getLocation() + getForward();
}

vec3 Camera::getUp()
{
	float pi = (float)M_PI;
	float x = cos(pitch + pi / 2) * sin(yaw);
	float y = sin(pitch + pi / 2);
	float z = -cos(pitch + pi / 2) * cos(yaw);
	return vec3(x, y, z);
}

vec3 Camera::getRight()
{
	return cross(getForward(), getUp());
}
