#include <iostream>

#define GLFW_INCLUDE_NONE
#define GLFW_DLL
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
#include "render/camera.h"
#include "render/mesh.h"
#include "render/shaderLoader.h"
#include "render/constants.h"
#include "render/model.h"

#include "physics/physicalObj.h"
//#include "boundary.h"
#include "physics/terrain.h"

#include <math.h>
#include <time.h>
#include <ctime>
#include "base/player.h"
#include "base/npc.h"

#include <stdio.h>

#include "sound/soundengine.h"
#include "sound/filesound.h"
#include "sound/voice.h"

glm::vec2 normalize(glm::vec2 vec) {
	float d = sqrt(vec.x * vec.x + vec.y * vec.y);
	vec.x /= d;
	vec.y /= d;
	return vec;
}

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


// Global variabels
glm::vec2 speed = glm::vec2(0.0f, 0.0f);

float VCAP = 0.1f;

Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
//PhysicalObj player = PhysicalObj(glm::vec3(0.0f, 0.0f, 0.0f));
Player player("player", 10, new PhysicalObj(glm::vec3(0.0f, 0.0f, 0.0f)), &camera);

glm::vec2 speedSide = glm::vec2(0.0f, 0.0f);
int direction = 1;
float directionSide = 0;
float velocity = 0.1f;

SoundEngine sound_engine;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	double xpos, ypos;
	double lastXPos, lastYPos;
	float sensivity = 0.1f;
	lastXPos = 0.0;
	lastYPos = 0.0;
	srand(time(0));

	// Check openAL
	ALuint source;
	alGenSources(1, &source);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_TRUE);

	FileSound sound(&sound_engine, &source, "resources/sounds/happierburial.wav");
	sound.Play();

	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "3O/\\0TAR >|<AbKA", nullptr, nullptr);

	//printf("%i\n", m_viewport[1]);

//	GLuint width, height = 

	glfwMakeContextCurrent(window);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();
	
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	// Define the viewport dimensions
	glViewport(0, 0, width, height);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Build and compile our shader program
	Shader ourShader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");

	// Set up vertex data (and buffer(s)) and attribute pointers
	Model planeModel = Model((char*)"resources/models/frog.obj");

        NPC test_npc("test_npc", 10,
                     new PhysicalObj(Mesh("resources/textures/stone.jpg", new Model((char *) "resources/models/frog.obj")),
                     false, true, false, glm::vec3(3.0f, 3.0f, 3.0f),
                     glm::vec3(0.0f, 0.0f, 0.0f), "frock"));

	Terrain terrain(100, 1.0f);
	PhysicalObj plane = PhysicalObj(Mesh("resources/textures/frog.jpg", &planeModel),
                                        false, true, false, glm::vec3(0.0f, 0.0f, 0.0f),
                                        glm::vec3(0.0f, 0.0f, 0.0f), "frog");

	// TEST CODE START

	Shader GUIShader("resources/shaders/GUI_vertex_shader.glsl", "resources/shaders/GUI_fragment_shader.glsl");

	std::vector<float> menuBox = {-0.9f,  0.9f, 0.0f,
								  -0.9f, -0.9f, 0.0f,
								   0.9f,  0.9f, 0.0f,
								   0.9f, -0.9f, 0.0f};
	std::vector<int> menuIndices = {0, 1, 2,
									1, 2, 3};

	GLuint VBO2, VAO2, EBO2;

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(menuBox[0]) * menuBox.size(), &(menuBox[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(menuIndices[0]) * menuIndices.size(), &(menuIndices[0]), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	// TEST CODE END


	while (!glfwWindowShouldClose(window))
	{
		
		lastXPos = xpos;
		lastYPos = ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		glm::vec2 cursorMotion = glm::vec2(lastXPos - xpos, lastYPos - ypos);
		if(cursorMotion.x != 0 || cursorMotion.y != 0) {
			if(speed.x != 0 || speed.y != 0) {
				speed.x = -sin(glm::radians(-player.GetCamera()->getRotation().y)) * velocity * direction;
				speed.y = -cos(glm::radians(-player.GetCamera()->getRotation().y)) * velocity * direction;
			}
			if(speedSide.x != 0 || speedSide.y != 0) {
				speedSide.x = -sin(glm::radians(-(player.GetCamera()->getRotation().y + directionSide))) * velocity;
				speedSide.y = -cos(glm::radians(-(player.GetCamera()->getRotation().y + directionSide))) * velocity;
			}
			cursorMotion *= sensivity;
			player.GetCamera()->changeRotationX(-cursorMotion.y);
			player.GetCamera()->changeRotationY(-cursorMotion.x);
			if(player.GetCamera()->getRotation().x < -90.0f)
				player.GetCamera()->setRotationX(-90.0f);
			if(player.GetCamera()->getRotation().x > 90.0f)
				player.GetCamera()->setRotationX(90.0f);
		}
		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		// Render
		// Clear the color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		terrain.draw(ourShader, &camera, width, height);
		float terrainHeight = terrain.getHeight(player.GetCamera()->getPosition());

		float Xchange = speed.x + speedSide.x;

		player.GetPhysicalObj()->changePositionX(Xchange);

		if(player.GetPhysicalObj()->getPosition().y < terrainHeight) {
			float diff = terrainHeight - player.GetPhysicalObj()->getPosition().y;
			if(diff > VCAP) {
				player.GetPhysicalObj()->changePositionY(diff * VCAP);
				player.GetPhysicalObj()->acceleration.y = 0.0f;
				player.GetPhysicalObj()->velocity.y = 0.0f;
			} else {
				player.GetPhysicalObj()->setPositionY(terrainHeight);
			}
			player.GetPhysicalObj()->acceleration.y = 0.0f;
		} else if(player.GetPhysicalObj()->getPosition().y > terrainHeight + 0.1) {
			player.GetPhysicalObj()->acceleration.y = -9.81f;
		} else {
			player.GetPhysicalObj()->acceleration.y = 0;
		}

		float Ychange = speed.y + speedSide.y;

		player.GetPhysicalObj()->changePositionZ(Ychange);

		if(player.GetPhysicalObj()->getPosition().y < terrainHeight) {
			float diff = terrainHeight - player.GetPhysicalObj()->getPosition().y;
			if(diff > VCAP) {
				player.GetPhysicalObj()->changePositionY(VCAP * diff);
				player.GetPhysicalObj()->acceleration.y = 0.0f;
				player.GetPhysicalObj()->velocity.y = 0.0f;
			} else {
				player.GetPhysicalObj()->setPositionY(terrainHeight);
			}
			player.GetPhysicalObj()->acceleration.y = 0.0f;
		} else if(player.GetPhysicalObj()->getPosition().y > terrainHeight + 0.1) {
			player.GetPhysicalObj()->acceleration.y = -9.81f;
		} else {
			player.GetPhysicalObj()->acceleration.y = 0;
		}

		terrainHeight = terrain.getHeight(player.GetCamera()->getPosition());

		if(player.GetPhysicalObj()->getPosition().y > terrainHeight) {
			player.GetPhysicalObj()->setOnGround(false);
		} else {
			player.GetPhysicalObj()->setOnGround(true);
		}

		plane.draw(ourShader, &camera, width, height);
                test_npc.GetPhysicalObj()->draw(ourShader, &camera, width, height);

		GLint k = glGetUniformLocation(GUIShader.Program, "time");
		
		GUIShader.Use();
		
		glUniform1f(k, clock() / 10000.0f);

		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, menuIndices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		player.GetPhysicalObj()->update();
		player.GetCamera()->setPosition(player.GetPhysicalObj()->getPosition());

		//plane2.draw(ourShader, &camera);
		plane.changeRotationX(9.0f);
		plane.changeRotationY(3.0f);
		plane.changeRotationZ(3.0f);

		glm::vec3 player_stalk_vec(0.0f, 0.0f, 0.0f);

		glm::vec3 player_pos = player.GetPhysicalObj()->getPosition();
		glm::vec3 stalker_pos = test_npc.GetPhysicalObj()->getPosition();

		player_stalk_vec = player_pos - stalker_pos;
		player_stalk_vec = normalize(player_stalk_vec);
		// if(player_pos.x > stalker_pos.x) player_stalk_vec.x = 1.0f;
		// if(player_pos.x < stalker_pos.x) player_stalk_vec.x = -1.0f;
		// if(player_pos.y > stalker_pos.y) player_stalk_vec.y = 1.0f;
		// if(player_pos.y < stalker_pos.y) player_stalk_vec.y = -1.0f;
		// if(player_pos.z > stalker_pos.z) player_stalk_vec.z = 1.0f;
		// if(player_pos.z < stalker_pos.z) player_stalk_vec.z = -1.0f;

		test_npc.GetPhysicalObj()->changePosition(player_stalk_vec * 10.0f);
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
		speed.x = -sin(glm::radians(-player.GetCamera()->getRotation().y)) * velocity;
		speed.y = -cos(glm::radians(-player.GetCamera()->getRotation().y)) * velocity;
		direction = 1;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE && direction > 0) {
		speed.x = 0.0f;
		speed.y = 0.0f;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		speed.x = sin(glm::radians(-player.GetCamera()->getRotation().y)) * velocity;
		speed.y = cos(glm::radians(-player.GetCamera()->getRotation().y)) * velocity;
		direction = -1;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE && direction < 0) {
		speed.x = 0.0f;
		speed.y = 0.0f;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		speedSide.x = sin(glm::radians(-(player.GetCamera()->getRotation().y + 90.0f))) * velocity;
		speedSide.y = cos(glm::radians(-(player.GetCamera()->getRotation().y + 90.0f))) * velocity;
		directionSide = -90.0f;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE && directionSide < 0.0f) {
		speedSide.x = 0.0f;
		speedSide.y = 0.0f;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		speedSide.x = sin(glm::radians(-(player.GetCamera()->getRotation().y - 90.0f))) * velocity;
		speedSide.y = cos(glm::radians(-(player.GetCamera()->getRotation().y - 90.0f))) * velocity;
		directionSide = 90.0f;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE && directionSide > 0.0f) {
		speedSide.x = 0.0f;
		speedSide.y = 0.0f;
	}
	if (key == GLFW_KEY_E) {
		player.GetCamera()->changePositionY(0.1f);
	}

	if (key == GLFW_KEY_Q) {
		player.GetCamera()->changePositionY(-0.1f);
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		player.GetPhysicalObj()->jump();//velocity.y = 10.0f;
	}
}

