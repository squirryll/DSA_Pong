#include <ShaderManager.h>
#include <Mesh.h>
#include <GameObject.h>
#include <Camera.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <vector>
#include <string>
#include <iostream>
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

// Player objects
GameObject p1(vec3(0, 0, 0));
GameObject p2(vec3(0, 0, 0));
GameObject ball(vec3(0, 0, 0));

// Some Game Variables
int pSpeed = 4;
int ballSpeed = 10;
int p1Score = 0;
int p2Score = 0;
vec3 ballVel = vec3(0, 0, 0);

// ----- Random number generation
float randomNumber(float min, float max)
{
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

// ----- CheckCollisions
void checkCollisions()
{
	if (ball.collidesWith(p1))
	{
		if (ballVel.x < 0)
		{
			ballVel.x = ball.location.x - p1.location.x;
			ballVel.y = ball.location.y - p1.location.y;
			ballVel = vec3(ballVel.x / ballVel.length() * ballSpeed, ballVel.y / ballVel.length() * ballSpeed, 0);
		}
	}

	if(ball.collidesWith(p2))
	{
		if (ballVel.x > 0)
		{
			ballVel.x = ball.location.x - p2.location.x;
			ballVel.y = ball.location.y - p2.location.y;
			ballVel = vec3(ballVel.x / ballVel.length() * ballSpeed, ballVel.y / ballVel.length() * ballSpeed, 0);
		}
	}
}

// Reset the initial velocity of the ball
void reset() {
	// Randomize starting direction
	int dir = rand() % 2;
	if (dir == 0) { ballVel = vec3(1, 0, 0); }
	else { ballVel = vec3(-1, 0, 0); }
	// Reset location
	ball.location = vec3(0, 0, 0);
	// Reset players
	p1.location = vec3(-2, 0, 0);
	p1.netForce = vec3(0, 0, 0);
	p1.velocity = vec3(0, 0, 0);
	p2.location = vec3(2, 0, 0);
	p2.netForce = vec3(0, 0, 0);
	p2.velocity = vec3(0, 0, 0);
	ball.location = vec3(0, 0, 0);
	ball.netForce = vec3(0, 0, 0);
	ball.velocity = vec3(0, 0, 0);
}

// ----- User input.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Player 1.
	if (key == GLFW_KEY_W)
	{	
		if(p1.location.y < 2)
			p1.netForce += vec3(0, pSpeed, 0);
	}
	else if (key == GLFW_KEY_S)
	{
		if (p1.location.y > -2)
			p1.netForce += vec3(0, -pSpeed, 0);
	}

	// Player 2.
	if (key == GLFW_KEY_UP)
	{
		if (p2.location.y < 2)
			p2.netForce += vec3(0, pSpeed, 0);
	}
	if (key == GLFW_KEY_DOWN)
	{
		if (p2.location.y > -2)
			p2.netForce += vec3(0, -pSpeed, 0);
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
		reset();
		p1Score = 0;
		p2Score = 0;
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
	//Mesh *poly = new Mesh("Poly.obj");

	// Assign player objects.
	p1 = GameObject(cube, shaderProgramIndex, vec3(-2, 0, 0), vec3(0.3, 1, 1), vec3(0, 0, 1));
	p2 = GameObject(cube, shaderProgramIndex, vec3(2, 0, 0), vec3(0.3, 1, 1), vec3(0, 0, 1));
	ball = GameObject(cube, shaderProgramIndex, vec3(0, 0, 0), vec3(0.3, 0.3, 0.3), vec3(0, 0, 1));

	// Set ball direction
	reset();

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

		// Update score board
		system("CLS");
		cout << p1Score << " | " << p2Score << endl;

		// Process queued window and input callback events.
		glfwPollEvents();

		/// TODO: Set up collision detection here to change ballVel

		// Update ball's velocity for movement
		ball.velocity = ballVel;

		// Update game objects.		
		cam.update(dt);
		p1.update(dt);
		p2.update(dt);
		ball.update(dt);

		// Check collisions
		checkCollisions();

		// Check if ball has hit top or bottom of screen, reverse y direction
		if (ball.location.y > 2) {
			ballVel.y *= -1;
		}
		if (ball.location.y < -2) {
			ballVel.y *= -1;
		}

		// Check if ball has left screen on either side, increment points
		if (ball.location.x > 3) {
			p1Score++;
			reset();
		}
		if (ball.location.x < -3) {
			p2Score++;
			reset();
		}

		// Ensure player paddles do not leave the screen
		if (p1.location.y > 2) {
			p1.location.y = 2;
			p1.velocity = vec3(0 ,0 ,0);
			p1.netForce = vec3(0, 0, 0);
		}
		if (p1.location.y < -2) { 
			p1.location.y = -2;
			p1.velocity = vec3(0, 0, 0);
			p1.netForce = vec3(0, 0, 0);
		}
		if (p2.location.y > 2) {
			p2.location.y = 2; 
			p2.velocity = vec3(0, 0, 0);
			p2.netForce = vec3(0, 0, 0);
		}
		if (p2.location.y < -2) { 
			p2.location.y = -2;
			p2.velocity = vec3(0, 0, 0);
			p2.netForce = vec3(0, 0, 0);
		}

		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw game objects.
		cam.draw();
		p1.draw();
		p2.draw();
		ball.draw();

		// Swap the front (what the screen displays) and back (what OpenGL draws to) buffers.
		glfwSwapBuffers(windowPtr);
	}

	// Clean up.
	delete cube;
	glfwTerminate();

	return 0;
}