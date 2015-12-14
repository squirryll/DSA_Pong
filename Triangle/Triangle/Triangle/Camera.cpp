#include "Camera.h"

Camera::Camera(GLuint shader, vec3 p):GameObject(p)
{
	uniformCameraMatrixLocation = glGetUniformLocation(shader, "camera");
}

// Overrides GameObject's draw so there is no need to have a mesh associated with Camera.
void Camera::draw() 
{
	mat4 cameraMatrix = perspective(3.14159f * .4f, 800.0f / 600.0f, .01f, 1000.f) * lookAt(location, vec3(0, 0, 0), vec3(0, 1, 0));
	glUniformMatrix4fv(uniformCameraMatrixLocation, 1, GL_FALSE, value_ptr(cameraMatrix));
}