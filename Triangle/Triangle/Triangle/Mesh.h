#pragma once
#include <ShaderManager.h>
#include <Camera.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include <SOIL.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
using namespace glm;

struct vert
{
	vec3 pos;
	vec2 uv;
	vec3 norm;
};

class Mesh {
public:
	Mesh();
	Mesh(const vector<vert> &verts, const vector<unsigned short> &elements);
	Mesh(string filename);
	~Mesh();
	void draw();
private:
	GLuint vaoIndex = 1;
	int numElements = 0;
};