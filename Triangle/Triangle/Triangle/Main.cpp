#include <ShaderManager.h>
#include <Mesh.h>
#include <GameObject.h>
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

//GameObject player1("Cube.obj", vec3(0, 0, -0.5));
//GameObject player2("Cube.obj", vec3(0, 0, 0.5));
//GameObject ball("Cube.obj", vec3(0, 0, 0));
//GameObject court("Cube.obj", vec3(0, -0.5, 0));

// ---- Global variables.

// Constants.
int WIDTH = 800;
int HEIGHT = 600;
float CAM_SPEED = 2.5f;

// World time.
float previousTime;

// Cube rotation variables.
bool mouseButtonHeld = false;
float angleChange = 0.0;	 

// Shader variables.
GLuint shaderProgramIndex;	 
mat4 model, view, projection, camera;
GLint c;
GLint m;
int floatsPerVert;
float fov;
float aspect;

// Camera.
Camera cam;

// User input for players.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Player 1.
	if (key == GLFW_KEY_W)
	{
		// Go up.
	}
	if (key == GLFW_KEY_S)
	{
		// Go down.
	}

	// Player 2.
	if (key == GLFW_KEY_UP)
	{
		// Go up.
	}
	if (key == GLFW_KEY_DOWN)
	{
		// Go down.
	}

	// Quit.
	if (key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE)
	{
		exit(0);
	}

	// Reset.
	if (key == GLFW_KEY_R)
	{
	
	}
}

void update(GLFWwindow* window)
{
	// Get change in time for smooth animation.
	float currentTime = glfwGetTime();
	float dt = currentTime - previousTime;
	previousTime = currentTime;

	// Update objects.


	// Update model matrix.
	model = translate(model, vec3(0, 0, 0));
	glUniformMatrix4fv(m, 1, GL_FALSE, value_ptr(model));
}

int main()
{
	// Initialize GLFW.
	if (!glfwInit()) {
		return -1;
	}

	// Create a windowed mode window.
	GLFWwindow* windowPtr = glfwCreateWindow(WIDTH, HEIGHT, "Pong", NULL, NULL);
	if (!windowPtr) {
		glfwTerminate();
		return -1;
	}

	// Make the new window the currently active window.
	glfwMakeContextCurrent(windowPtr);

	// Set up input callbacks.
	glfwSetKeyCallback(windowPtr, key_callback);

	// Hide cursor.
	glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Initialize GLEW.
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}

	// Load shader.
	GLuint shaderProgramIndex = ShaderManager::loadShaderProgram("vertex.glsl", "fragment.glsl");
	if (shaderProgramIndex == 0) {
		glfwTerminate();
		return -1;
	}
	glUseProgram(shaderProgramIndex);

	Mesh *mesh = new Mesh("Cube.obj");
	GameObject p1(mesh);
	GameObject p2(mesh);

	// Engage drawing modes.
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	// Set up model matrix.
	m = glGetUniformLocation(shaderProgramIndex, "model");
	glUniformMatrix4fv(m, 1, GL_FALSE,value_ptr(model));

	// Set up projection matrix.
	fov = M_PI / 2.0f;
	aspect = WIDTH / HEIGHT;
	projection = perspective(fov, 1.3f, .01f, 1000.0f);

	// Set up view matrix.
	view = lookAt(cam.getLocation(), cam.getLookAt(), cam.getUp());

	// Set up camera matrix.
	camera = projection * view;
	c = glGetUniformLocation(shaderProgramIndex, "camera");
	glUniformMatrix4fv(c, 1, GL_FALSE, value_ptr(camera));

	// Main game loop.
	while (!glfwWindowShouldClose(windowPtr))
	{
		// Process queued window and input callback events.
		glfwPollEvents();

		// Update most things.
		//p1.update();
		update(windowPtr);

		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw mesh.
		p1.draw();
		p2.draw();

		// Swap the front (what the screen displays) and back (what OpenGL draws to) buffers.
		glfwSwapBuffers(windowPtr);
	}

	delete mesh;
	glfwTerminate();
	return 0;
}