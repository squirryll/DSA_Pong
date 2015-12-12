#pragma once
#include "glm.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace glm;
using namespace std;

struct vert
{
	vec3 pos;
	vec2 uv;
	vec3 norm;
};

class GameObject
{
public:
	GameObject(string filename, vec3 pos);
	~GameObject();
	vector<vert> loadOBJVerts(string filename);
	vector<unsigned short> loadOBJElements(string filename);
	void setPos(vec3 pos);
	void setVel(vec3 vel);
	vec3 getPos();
	vec3 getVel();
	vector<vert> getVerts();
	vector<unsigned short> getElems();
	
private:
	vec3 velocity;
	vec3 position;
	vector<vert> verts;
	vector<unsigned short> elements;
};