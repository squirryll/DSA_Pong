#pragma once
#include "glm.hpp"
#include "gtx/transform.hpp"
#include <gtc/type_ptr.hpp>
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
	GameObject(vec3 p);
	GameObject(Mesh *m, GLuint shaderProgramIndex, vec3 p, vec3 s, vec3 r);
	void update(float dt);
	void draw();
	bool collidesWith(GameObject otherObj);
	vec3 location;
	vec3 size;
	float rAngle;
	vec3 rAxis;
	vec3 velocity;
	float angularVelocity;
	vec3 netForce;
	float mass;
	Mesh *mesh;
	GLuint shaderProgramIndex;
	vec3 getHalfWidths();
};