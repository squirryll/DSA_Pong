#pragma once
#include "glm.hpp"
#include "gtx\transform.hpp"
#include "GameObject.h"
using namespace glm;

// Camera extends GameObject so it's able to be repositioned.
class Camera:public GameObject
 {
public:
	 Camera(GLuint shader, vec3 p);
	 void draw();
private:
	GLint uniformCameraMatrixLocation;
};