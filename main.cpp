#include <iostream>

#define GLFW_INCLUDE_NONE
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#ifndef GLWF_ALREADY_INCLUDED
#define GLWF_ALREADY_INCLUDED
#include <GLFW/glfw3.h>
#endif

// Other Libs
// GLM Mathematics
#include <glm/gtx/string_cast.hpp>

// Other includes
#include "render/mesh.h"
#include "render/shaderLoader.h"
#include "render/constants.h"
#include "render/model.h"
#include "render/camera.h"
//#include "boundary.h"
#include <math.h>

glm::vec2 normalize(glm::vec2 vec) {
	float d = sqrt(vec.x * vec.x + vec.y * vec.y);
	//std::cout << d << std::endl;
	vec.x /= d;
	vec.y /= d;
	return vec;
}

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Window dimensions
// glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
// glm::vec3 cameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec2 speed = glm::vec2(0.0f, 0.0f);

Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));

glm::vec2 speedSide = glm::vec2(0.0f, 0.0f);
int direction = 1;
float directionSide = 0;
float velocity = 0.1f;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	double xpos, ypos;
	double lastXPos, lastYPos;
	float sensivity = 0.1f;
	lastXPos = 0.0;
	lastYPos = 0.0;
	srand(time(0));
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glEnable(GL_DEPTH_TEST);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Build and compile our shader program
	Shader ourShader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");

	// Set up vertex data (and buffer(s)) and attribute pointers
	Model Plane = Model((char*)"resources/models/plane.obj");

	Mesh plane = Mesh("resources/textures/stone.jpg", Plane.vertices, Plane.indices, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -2.0f, 0.0f));

	// Create transformations

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		camera.changePositionX(speed.x + speedSide.x);
		camera.changePositionZ(speed.y + speedSide.y);
		lastXPos = xpos;
		lastYPos = ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		glm::vec2 cursorMotion = glm::vec2(lastXPos - xpos, lastYPos - ypos);
		if(cursorMotion.x != 0 || cursorMotion.y != 0) {
			if(speed.x != 0 || speed.y != 0) {
				speed.x = -sin(glm::radians(-camera.getRotation().y)) * velocity * direction;
				speed.y = -cos(glm::radians(-camera.getRotation().y)) * velocity * direction;
			}
			if(speedSide.x != 0 || speedSide.y != 0) {
				speedSide.x = -sin(glm::radians(-(camera.getRotation().y + directionSide))) * velocity;
				speedSide.y = -cos(glm::radians(-(camera.getRotation().y + directionSide))) * velocity;
			}
			cursorMotion *= sensivity;
			camera.changeRotationX(-cursorMotion.y);
			camera.changeRotationY(-cursorMotion.x);
			if(camera.getRotation().x < -90.0f)
				camera.setRotationX(-90.0f);
			if(camera.getRotation().x > 90.0f)
				camera.setRotationX(90.0f);
		}
		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		// Render
		// Clear the color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		plane.draw(ourShader, camera.getRotation(), camera.getPosition());

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		speed.x = -sin(glm::radians(-camera.getRotation().z)) * velocity;
		speed.y = -cos(glm::radians(-camera.getRotation().z)) * velocity;
		direction = 1;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE && direction > 0) {
		speed.x = 0.0f;
		speed.y = 0.0f;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		speed.x = sin(glm::radians(-camera.getRotation().z)) * velocity;
		speed.y = cos(glm::radians(-camera.getRotation().z)) * velocity;
		direction = -1;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE && direction < 0) {
		speed.x = 0.0f;
		speed.y = 0.0f;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		speedSide.x = sin(glm::radians(-(camera.getRotation().z + 90.0f))) * velocity;
		speedSide.y = cos(glm::radians(-(camera.getRotation().z + 90.0f))) * velocity;
		directionSide = -90.0f;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE && directionSide < 0.0f) {
		speedSide.x = 0.0f;
		speedSide.y = 0.0f;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		speedSide.x = sin(glm::radians(-(camera.getRotation().z - 90.0f))) * velocity;
		speedSide.y = cos(glm::radians(-(camera.getRotation().z - 90.0f))) * velocity;
		directionSide = 90.0f;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE && directionSide > 0.0f) {
		speedSide.x = 0.0f;
		speedSide.y = 0.0f;
	}
}