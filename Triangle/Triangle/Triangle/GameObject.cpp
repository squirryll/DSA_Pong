#include "GameObject.h"

GameObject::GameObject()
{
	location = vec3(0, 0, 0);
	size = vec3(1, 1, 1);
	rAxis = vec3(0, 0, 1);
	velocity = vec3(0, 0, 0);
	netForce = vec3(0, 0, 0);
	angularVelocity = 0;
	rAngle = 0;
	mass = 1;
}

GameObject::GameObject(vec3 p)
{
	location = p;
	size = vec3(1, 1, 1);
	rAxis = vec3(0, 0, 1);
	velocity = vec3(0, 0, 0);
	netForce = vec3(0, 0, 0);
	angularVelocity = 0;
	rAngle = 0;
	mass = 1;
}

GameObject::GameObject(Mesh *m, GLuint shader, vec3 p, vec3 s, vec3 r)
{
	mesh = m;
	location = p;
	size = s;
	rAxis = r;
	velocity = vec3(0, 0, 0);
	netForce = vec3(0, 0, 0);
	angularVelocity = 0;
	rAngle = 0;
	mass = 1;
	shaderProgramIndex = shader;
}

void GameObject::draw()
{
	mat4 worldMatrix = translate(location) * scale(size) * rotate(rAngle, rAxis);
	GLint uniformWorldMatrixLocation = glGetUniformLocation(shaderProgramIndex, "worldMatrix");
	glUniformMatrix4fv(uniformWorldMatrixLocation, 1, GL_FALSE, value_ptr(worldMatrix));

	mesh->draw();
}

bool GameObject::collidesWith(GameObject otherObj)
{
	vec3 maxA = this->location + this->getHalfWidths();
	vec3 minA = this->location - this->getHalfWidths();
	vec3 maxB = otherObj.location + otherObj.getHalfWidths();
	vec3 minB = otherObj.location - otherObj.getHalfWidths();

	return (maxA.x > minB.x &&
		minA.x < maxB.x &&
		maxA.y > minB.y &&
		minA.y < maxB.y &&
		maxA.z > minB.z &&
		minA.z < maxB.z);
}

vec3 GameObject::getHalfWidths()
{
	float x = (float)size.x / 2;
	float y = (float)size.y / 2;
	float z = (float)size.z / 2;

	return vec3(x, y, z);
}

void GameObject::update(float dt)
{
	//netForce += vec3(0, -0.5, 0); // Gravity
	netForce += -velocity * 0.5f; // Drag
	velocity += (dt * netForce) / mass;
	location += velocity * dt;
	netForce = vec3(0);
}
