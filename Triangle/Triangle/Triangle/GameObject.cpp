#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(Mesh *m, vec3 pos)
{
	mesh = m;
	velocity = vec3(0);
	position = pos;
}
void GameObject::setPos(vec3 pos)
{
	position = pos;
}

vec3 GameObject::getPos()
{
	return position;
}

vec3 GameObject::getVel()
{
	return velocity;
}

void GameObject::setVel(vec3 vel)
{
	velocity = vel;
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
	delete mesh;
}
