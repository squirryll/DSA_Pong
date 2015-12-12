#pragma once
#define _USE_MATH_DEFINES
#include "glm.hpp"
#include "gtx\transform.hpp"
#include <math.h>
using namespace glm;

class Camera
{
public:
	Camera();
	~Camera();
	void turn(float dx, float dy);
	vec3 getLocation();
	void move(vec3 movement);
	vec3 getForward();
	vec3 getLookAt();
	vec3 getUp();
	vec3 getRight();
private:
	float yaw;
	float pitch;
	vec3 pos;
};