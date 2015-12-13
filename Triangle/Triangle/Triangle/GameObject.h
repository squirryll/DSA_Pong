#pragma once
#include "glm.hpp"
#include "Mesh.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace glm;
using namespace std;

class GameObject
{
public:
	GameObject();
	GameObject(Mesh *m, vec3 pos);
	~GameObject();
	void setPos(vec3 pos);
	void setVel(vec3 vel);
	vec3 getPos();
	vec3 getVel();
	void update();
	void draw();
	
private:
	vec3 velocity;
	vec3 position;
	Mesh *mesh;
};