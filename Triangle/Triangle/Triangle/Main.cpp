#include <ShaderManager.h>
#include <Mesh.h>
#include <GameObject.h>
#include <Camera.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace glm;

// ----- Global variables.

// Window constants.
int WIDTH = 800;
int HEIGHT = 600;

// World time.
float previousTime;

// Shader program.
GLuint shaderProgramIndex;	 


// ----- User input.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Player 1.
	if (key == GLFW_KEY_W)
	{
		/// TODO: Go up. (Alter netForce of GameObject in upward direction)
	}
	if (key == GLFW_KEY_S)
	{
		/// TODO: Go down.
	}

	// Player 2.
	if (key == GLFW_KEY_UP)
	{
		/// TODO: Go up.
	}
	if (key == GLFW_KEY_DOWN)
	{
		/// TODO: Go down.
	}

	// Quit.
	if (key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE)
	{
		exit(0);
	}

	// Reset.
	if (key == GLFW_KEY_R)
	{
		/// TODO: Reset game.
	}
}

int main()
{
	// Initialize GLFW.
	if (!glfwInit()) {
		return -1;
	}

	// Create a windowed mode window.
	GLFWwindow* windowPtr = glfwCreateWindow(WIDTH, HEIGHT, "[Game Name!]", NULL, NULL);
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

	// Initialize camera.
	Camera cam(shaderProgramIndex, vec3(0, 0, 3));

	// Initialize basic cube mesh.
	Mesh *cube = new Mesh("Cube.obj");

	// Create player objects.
	GameObject p1(cube, shaderProgramIndex, vec3(-1.5, 0, 0), vec3(0.3, 1, 1), vec3(0, 0, 1));
	GameObject p2(cube, shaderProgramIndex, vec3(1.5, 0, 0), vec3(0.3, 1, 1), vec3(0, 0, 1));

	// Engage drawing modes.
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	// Main game loop.
	while (!glfwWindowShouldClose(windowPtr))
	{
		// Get change in time for smooth animation.
		float currentTime = glfwGetTime();
		float dt = currentTime - previousTime;
		previousTime = currentTime;

		// Process queued window and input callback events.
		glfwPollEvents();

		// Update game objects.
		cam.update(dt);
		p1.update(dt);
		p2.update(dt);

		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw game objects.
		cam.draw();
		p1.draw();
		p2.draw();

		// Swap the front (what the screen displays) and back (what OpenGL draws to) buffers.
		glfwSwapBuffers(windowPtr);
	}

	// Clean up.
	delete cube;
	glfwTerminate();

	return 0;
}