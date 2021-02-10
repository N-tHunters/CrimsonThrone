#include <iostream>
#include <math.h>
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <map>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#endif

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
#include <render/camera.hpp>
#include <render/mesh.hpp>
#include <render/shaderLoader.hpp>
#include <render/constants.hpp>
#include <render/model.hpp>
#include <render/imageLoader.hpp>

#include <physics/physicalObj.hpp>
#include <physics/boundary.hpp>
#include <physics/terrain.hpp>

#include <base/player.hpp>
#include <base/npc.hpp>
#include <base/item.hpp>
#include <base/chunk.hpp>
#include <base/location.hpp>
#include <base/shortjumptrigger.hpp>

#include <base/magic/core.h>
#include <base/magic/symbols.h>

#include <sound/soundengine.h>
#include <sound/filesound.h>
#include <sound/voice.h>

#include <UI/frame.hpp>
#include <UI/list.hpp>
#include <UI/container.hpp>
#include <UI/bar.hpp>
#include <UI/text.hpp>
#include <UI/abstractListElement.hpp>
#include <UI/button.hpp>

#include <landscape/dungeona1generator.hpp>

#include <base/configuration.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#define NO_SOUND

const std::string CONFIG_FILE = "resources/settings.ini";

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Global variabels
glm::vec2 speed = glm::vec2(0.0f, 0.0f);
glm::vec2 speedSide = glm::vec2(0.0f, 0.0f);

float VCAP = 0.1f;
Camera* camera;
Player* player;
SoundEngine sound_engine;
MagicCore * player_core;

Location * location;

int direction = 1;
float directionSide = 0;
float velocity = 10.0f;
bool player_wants_to_jump = false;

std::map<GLchar, Character> Characters;

bool push = false;
float push_m = 0.0f;
void load_characters();

enum {
	STATE_LOADING,
	STATE_RUNNING,
	STATE_PAUSED
} game_state;

void useless() {
	int a = 1;
	printf("%d\n", a);
}

int main()
{
	game_state = STATE_LOADING;
	camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	player = new Player("player", 10, new PhysicalObj(glm::vec3(3.0f, 1.0f, 3.0f), new BoundaryBox(0.25f, 1.0f, 0.25f)), camera);
	player_core = new MagicCore();
	player_core->SetPhysicalObj(player->GetPhysicalObj());

	init_translators();
	init_protocores();
	LoadConfiguration(CONFIG_FILE);

	double xpos, ypos;
	xpos = 0.0;
	ypos = 0.0;
	float sensivity = 0.1f;
	srand(time(0));

	// Check openAL
	ALuint source;
	alGenSources(1, &source);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_TRUE);

#ifndef NO_SOUND
	FileSound sound(&sound_engine, &source, "resources/sounds/happierburial.wav");
	sound.Play();
#endif

	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Crimson Throne", nullptr, nullptr);

	glfwMakeContextCurrent(window);

#ifdef _WIN32
	// Turn on vertical screen sync under Windows.
	// (I.e. it uses the WGL_EXT_swap_control extension)
	typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXTPROC)(int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapIntervalEXT) {
		wglSwapIntervalEXT(0);
	}
#endif

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

	// LOADING ICON

	/*int icon_width, icon_height;
	unsigned char * icon = loadImage("resources/textures/icon.jpeg", &icon_width, &icon_height);
	GLFWimage icon_image[1];
	icon_image[0].pixels = icon;
	icon_image[0].width = 32;
	icon_image[0].height = 32;
	glfwSetWindowIcon(window, 1, icon_image);
	freeImage(icon);*/

	// Frame buffer

	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// создание текстурного объекта
	unsigned int texColorBuffer;
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// присоедиение текстуры к объекту текущего кадрового буфера
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);


	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	load_characters();

	// Build and compile our shader program
	Shader ourShader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");
	Shader GUIShader("resources/shaders/GUI_vertex_shader.glsl", "resources/shaders/GUI_fragment_shader.glsl");
	Shader textShader("resources/shaders/GUI_vertex_shader.glsl", "resources/shaders/text_fragment_shader.glsl");
	Shader waterShader("resources/shaders/water_vertex_shader.glsl", "resources/shaders/water_fragment_shader.glsl");
	Shader postShader("resources/shaders/post_vertex_shader.glsl", "resources/shaders/post_fragment_shader.glsl");

	ShaderHolder* shaderHolder = new ShaderHolder(&ourShader,
	        &GUIShader,
	        &textShader,
	        &waterShader,
	        &postShader);

	// ----------------------------------------------- CODE ------------------------------------------
	location = new Location(10, 10, 10, 10, new DungeonA1Generator(10));

	SetCurrentLocation(location);

	Text* fps_counter = new Text(std::to_string(0.0f), glm::vec4(0.8f, 0.8f, 0.1f, 0.1f), Characters, 0.001f, glm::vec3(0, 0, 0));

	float last_frame = glfwGetTime();
	int hp = player->GetHealth();
	int maxHp = player->GetMaxHealth();

	player->GetPhysicalObj()->name = "Player";

	Bar test_frame(glm::vec4(-0.9f, 0.9f, 0.5f, 0.1f), &hp, &maxHp, glm::vec3(255.0, 0, 0));

	float fps_change_last = 0.0f;

	GLuint quadVAO, quadVBO, quadEBO;

	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
	glGenBuffers(1, &quadVBO);
	glGenBuffers(1, &quadEBO);

	glBindVertexArray(quadVAO);

	std::vector<float>* quad_vertices = new std::vector<float> {
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f
	};

	std::vector<unsigned int>* quad_indices = new std::vector<unsigned int> {
		0, 1, 2,
		0, 2, 3
	};

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices->at(0)) * quad_vertices->size(), &(quad_vertices->at(0)), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices->at(0)) * quad_indices->size(), &(quad_indices->at(0)), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glfwSetCursorPos(window, (double)width / 2.0, (double)height / 2.0);

	typedef void (*function)();
	Button* button = new Button(glm::vec4(-0.1f, -0.1f, 0.2f, 0.2f), (function)useless, "bruh", Characters, 14.0f, glm::vec3(255.0f, 255.0f, 0.0f), width, height);

	game_state = STATE_RUNNING;

	while (!glfwWindowShouldClose(window))
	{
		if (camera->getRotationX() > 180.0f) {
			camera->setRotationX(-180.0f);
		}
		if (camera->getRotationX() < -180.0f) {
			camera->setRotationX(180.0f);
		}
		if (camera->getRotationY() > 180.0f) {
			camera->setRotationY(-180.0f);
		}
		if (camera->getRotationY() < -180.0f) {
			camera->setRotationY(180.0f);
		}
		if (camera->getRotationZ() > 180.0f) {
			camera->setRotationZ(-180.0f);
		}
		if (camera->getRotationZ() < -180.0f) {
			camera->setRotationZ(180.0f);
		}

		float dt;
		float current_frame;
		float lastXPos = xpos;
		float lastYPos = ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		glm::vec2 cursorMotion = glm::vec2(lastXPos - xpos, lastYPos - ypos);
		if (game_state != STATE_PAUSED) {
			if (cursorMotion.x != 0 || cursorMotion.y != 0) {
				if (speed.x != 0 || speed.y != 0) {
					speed.x = -sin(glm::radians(-player->GetCamera()->getRotation().y)) * velocity * direction;
					speed.y = -cos(glm::radians(-player->GetCamera()->getRotation().y)) * velocity * direction;
				}
				if (speedSide.x != 0 || speedSide.y != 0) {
					speedSide.x = -sin(glm::radians(-(player->GetCamera()->getRotation().y + directionSide))) * velocity;
					speedSide.y = -cos(glm::radians(-(player->GetCamera()->getRotation().y + directionSide))) * velocity;
				}
				cursorMotion *= sensivity;
				player->GetCamera()->changeRotationX(-cursorMotion.y);
				player->GetCamera()->changeRotationY(-cursorMotion.x);
				if (player->GetCamera()->getRotation().x < -90.0f)
					player->GetCamera()->setRotationX(-90.0f);
				if (player->GetCamera()->getRotation().x > 90.0f)
					player->GetCamera()->setRotationX(90.0f);
			}
		}

		glfwPollEvents();

		/*glClearColor(0.5f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/


		// первый проход
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // буфер трафарета не используется
		glEnable(GL_DEPTH_TEST);

		glClearColor(0.5f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (game_state != STATE_PAUSED) {
			location->UpdatePosition(player->GetPhysicalObj()->getPosition());

			Chunk * chunk_ptr = location->GetCurrentChunk();
			if (chunk_ptr == nullptr)
				chunk_ptr = location->GetChunkByPosition(0, 0);

			if (player_wants_to_jump) {
				player->GetPhysicalObj()->jump(chunk_ptr);
			}


			player->GetPhysicalObj()->setSpeed(speed + speedSide);
			int chunk_ix = chunk_ptr->GetX();
			int chunk_iy = chunk_ptr->GetY();
			for (int dx = -1; dx <= 1; dx++) {
				for (int dy = -1; dy <= 1; dy++) {
					int nx = chunk_ix + dx;
					int ny = chunk_iy + dy;
					Chunk * nchunk = chunk_ptr->GetLocation()->GetChunk(nx, ny);
					if (nchunk == nullptr) continue;
					nchunk->CollideWithAll(player->GetPhysicalObj(), dt, true);
				}
			}
			player->Update(dt);

			/* Collide player with all objects in chunk */
			player->GetPhysicalObj()->collideTerrain(chunk_ptr->GetTerrain(), dt, chunk_ptr);

			chunk_ptr->CheckAllTriggers(player->GetPhysicalObj());
		}

		location->Draw(shaderHolder, camera, width, height);

		// второй проход
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // возвращаем буфер кадра по умолчанию
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderHolder->getPost()->Use();
		glUniform1f(glGetUniformLocation(shaderHolder->getPost()->Program, "speed"), sqrt(player->GetPhysicalObj()->velocity.x * player->GetPhysicalObj()->velocity.x + 
																						  player->GetPhysicalObj()->velocity.y * player->GetPhysicalObj()->velocity.y + 
																						  player->GetPhysicalObj()->velocity.z * player->GetPhysicalObj()->velocity.z));

		glBindVertexArray(quadVAO);
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// inventory->draw(shaderHolder);
		fps_counter->draw(shaderHolder);
		test_frame.draw(shaderHolder);

		if (game_state == STATE_PAUSED)
			button->draw(shaderHolder);

		glFinish();

		glfwSwapBuffers(window);

		if (game_state != STATE_PAUSED) {
			player_core->Step();
			location->Update(dt);
			current_frame = glfwGetTime();
			dt = (current_frame - last_frame);
			last_frame = current_frame;

			if (glfwGetTime() - fps_change_last > 0.1) {
				fps_counter->update(std::to_string((int)round(1.0 / dt)), Characters);
				fps_change_last = glfwGetTime();
			}
		} else {
			last_frame = glfwGetTime();
		}

		player_wants_to_jump = false; // What the fuck
		push = false;
	}
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		if (game_state != STATE_PAUSED) game_state = STATE_PAUSED;
		else game_state = STATE_RUNNING;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		speed.x = -sin(glm::radians(-player->GetCamera()->getRotation().y)) * velocity;
		speed.y = -cos(glm::radians(-player->GetCamera()->getRotation().y)) * velocity;
		direction = 1;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE && direction > 0) {
		speed.x = 0.0f;
		speed.y = 0.0f;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		speed.x = sin(glm::radians(-player->GetCamera()->getRotation().y)) * velocity;
		speed.y = cos(glm::radians(-player->GetCamera()->getRotation().y)) * velocity;
		direction = -1;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE && direction < 0) {
		speed.x = 0.0f;
		speed.y = 0.0f;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		speedSide.x = sin(glm::radians(-(player->GetCamera()->getRotation().y + 90.0f))) * velocity;
		speedSide.y = cos(glm::radians(-(player->GetCamera()->getRotation().y + 90.0f))) * velocity;
		directionSide = -90.0f;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE && directionSide < 0.0f) {
		speedSide.x = 0.0f;
		speedSide.y = 0.0f;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		speedSide.x = sin(glm::radians(-(player->GetCamera()->getRotation().y - 90.0f))) * velocity;
		speedSide.y = cos(glm::radians(-(player->GetCamera()->getRotation().y - 90.0f))) * velocity;
		directionSide = 90.0f;
	}

	if (key == GLFW_KEY_D && action == GLFW_RELEASE && directionSide > 0.0f) {
		speedSide.x = 0.0f;
		speedSide.y = 0.0f;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		// player->GetPhysicalObj()->jump();//velocity.y = 10.0f;
		player_wants_to_jump = true;
	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		//player->PickupItem(chunk);
	}

	if (key == GLFW_KEY_E) {
		push = true;
		push_m = -1.0;
	}

	if (key == GLFW_KEY_R) {
		push = true;
		push_m = 1.0;
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		std::string pseudo;
		std::cin >> pseudo;

		SYMBOL prog[1024];

		pseudo_to_prog(pseudo, prog);

		player_core->LoadProgram(prog, pseudo.length() + 1);
	}
}

void load_characters() {
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	FT_Face face;
	if (FT_New_Face(ft, "resources/fonts/hamburger.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;


	FT_Set_Pixel_Sizes(face, 0, 256);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
		    GL_TEXTURE_2D,
		    0,
		    GL_RED,
		    face->glyph->bitmap.width,
		    face->glyph->bitmap.rows,
		    0,
		    GL_RED,
		    GL_UNSIGNED_BYTE,
		    face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
		// Characters[c] = character;
	}

	FT_Done_Face(face);   // Завершение работы с шрифтом face
	FT_Done_FreeType(ft); // Завершение работы FreeType
}
