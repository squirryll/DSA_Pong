// Borrowed from class notes.

#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm.hpp"
#include <iostream>
#include <fstream>
using namespace std;
using namespace glm;

class ShaderManager
{
public:
	static char* loadTextFile(const char* file);
	static GLuint loadShader(const char* file, GLenum shaderType);
	static GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);

private:
	ShaderManager(void);
	~ShaderManager(void);
};

