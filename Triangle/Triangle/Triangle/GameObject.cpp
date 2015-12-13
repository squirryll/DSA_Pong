#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(Mesh *m, GLuint shaderProgramIndex)
{
	mesh = m;
	location = vec3(0);
	size = vec3(1);
	rAxis = vec3(0, 0, 1);
	velocity = vec3(0);
	netForce = vec3(0);
	angularVelocity = 0;
	rAngle = 0;
	mass = 1;
}

void GameObject::draw()
{
	mat4 worldMatrix = translate(location) * scale(size) * rotate(rAngle, rAxis);
	GLint uniformWorldMatrixLocation = glGetUniformLocation(shaderProgramIndex, "worldMatrix");
	glProgramUniformMatrix4fv(shaderProgramIndex, uniformWorldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
	mesh->draw();
}

void GameObject::update(float dt)
{
	//netForce += vec3(0, -9.81, 0); // Gravity
	//netForce += -velocity * 0.2f; // Drag
	//velocity += (dt * netForce) / mass;
	//location += velocity * dt;
	//netForce = vec3(0);
}

GameObject::~GameObject()
{

}
