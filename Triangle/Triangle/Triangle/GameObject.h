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
	GameObject(Mesh *m);
	~GameObject();
	void update();
	void draw();
	
private:
	vec3 location;
	vec3 size;
	float rAngle;
	vec3 rAxis;
	vec3 velocity;
	float angularVelocity;
	vec3 netForce;
	float mass;
	Mesh *mesh;
};