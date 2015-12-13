#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(Mesh *m)
{
	mesh = m;
	vec3 location = vec3(0);
	vec3 scale = vec3(1);
	vec3 rAxis = vec3(0, 0, 1);
	vec3 velocity = vec3(0);
	vec3 netForce = vec3(0);
	float angularVelocity = 0;
	float rAngle = 0;
	float mass = 1;
}

void GameObject::draw()
{
	mesh->draw();
}

void GameObject::update()
{

}

GameObject::~GameObject()
{

}
