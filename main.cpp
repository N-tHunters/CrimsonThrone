#include <iostream>
#include <math.h>
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <map>
#include <unistd.h>

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
//#include "render/shaders.h"

#include "physics/physicalObj.h"
//#include "boundary.h"
#include "physics/terrain.h"

#include "base/player.h"
#include "base/npc.h"
#include "base/item.h"
#include "base/chunk.h"

#include "sound/soundengine.h"
#include "sound/filesound.h"
#include "sound/voice.h"

#include "UI/frame.h"
//#include "UI/list.h"
#include "UI/container.h"
#include "UI/bar.h"
#include "UI/text.h"

#include <ft2build.h>
#include FT_FREETYPE_H

glm::vec2 normalize(glm::vec2 vec) {
  float d = sqrt(vec.x * vec.x + vec.y * vec.y);
  vec.x /= d;
  vec.y /= d;
  return vec;
}

glm::vec3 normalize(glm::vec3 vec) {
  float d = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
  vec.x /= d;
  vec.y /= d;
  vec.z /= d;
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
SoundEngine sound_engine;



glm::vec2 speedSide = glm::vec2(0.0f, 0.0f);
int direction = 1;
float directionSide = 0;
float velocity = 0.1f;

std::map<GLchar, Character> Characters;

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
  GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Crimson Throne", nullptr, nullptr);

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

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

  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
  FT_Face face;
  if (FT_New_Face(ft, "resources/fonts/hamburger.ttf", 0, &face))
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;


  FT_Set_Pixel_Sizes(face, 0, 48);

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
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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

  // Build and compile our shader program
  Shader ourShader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");
  Shader GUIShader("resources/shaders/GUI_vertex_shader.glsl", "resources/shaders/GUI_fragment_shader.glsl");
  Shader textShader("resources/shaders/GUI_vertex_shader.glsl", "resources/shaders/text_fragment_shader.glsl");


  // ----------------------------------------------- CODE ------------------------------------------

  Chunk chunk1(new Terrain(100, 1.0f));


  // Set up vertex data (and buffer(s)) and attribute pointers
  chunk1.AddActor((Actor*)
		  new NPC("test_npc", 10,
			  new PhysicalObj(Mesh("resources/textures/stone.jpg", new Model((char *) "resources/models/frog.obj")),
					  false, true, false, glm::vec3(3.0f, 3.0f, 3.0f),
					  glm::vec3(0.0f, 0.0f, 0.0f), "frock")));

  chunk1.AddObject(new PhysicalObj(Mesh("resources/textures/frog.jpg", new Model((char *) "resources/models/frog.obj")),
				   false, true, false, glm::vec3(0.0f, 0.0f, 0.0f),
				   glm::vec3(0.0f, 0.0f, 0.0f), "frog"));
	
  chunk1.AddItem(new Item("test_item", new PhysicalObj(Mesh("resources/textures/stone.jpg", new Model((char*)"resources/models/hammah.obj")), false, true, false, glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), "hammah!")));


  
  //List<Item*> inventory(glm::vec4(-0.9f, -0.9f, 1.8f, 1.8f), player.GetInventoryPointer(), std::string("resources/textures/list.png"), 10);
  Text* text = new Text("LMAO Bottom text", glm::vec4(-0.9f, -0.9f, 0.0f, 0.0f), Characters, 32.0f / (float)width / 16.0f, glm::vec3(0, 255, 0));
  //Container test_con(glm::vec4(-0.9f, -0.9f, 1.8f, 1.8f), text, "resources/textures/stone.jpg");

  float last_frame = glfwGetTime(),
    current_frame = glfwGetTime();

  float dt = 0.0f;
  int maxDt = 1;

  int hp = player.GetHealth();
  int maxHp = player.GetMaxHealth();

  player.GetPhysicalObj()->name = "Player";

  Bar test_frame(glm::vec4(-0.9f, 0.9f, 0.5f, 0.1f), &hp, &maxHp, glm::vec3(255, 0, 0));

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

      chunk1.Draw(&ourShader, &camera, width, height);

      player.GetPhysicalObj()->collideTerrain(chunk1.GetTerrain(), speed + speedSide, VCAP);

      /*		
		
      hammah.GetPhysicalObj()->collideTerrain(&terrain, glm::vec2(0.0f, 0.0f), VCAP);

      terrain.draw(&ourShader, &camera, width, height);

      plane.draw(&ourShader, &camera, width, height);
      */

      test_frame.draw(&GUIShader);
      text->draw(&textShader);
      // inventory.draw(&GUIShader);

      /*      
      glm::vec2 player_stalk_vec(0.0f, 0.0f);

      glm::vec3 player_pos = player.GetPhysicalObj()->getPosition();
      glm::vec3 stalker_pos = test_npc.GetPhysicalObj()->getPosition();

      player_stalk_vec = glm::vec2(player_pos.x - stalker_pos.x, player_pos.z - stalker_pos.z);
      player_stalk_vec = normalize(player_stalk_vec); 

      test_npc.GetPhysicalObj()->collideTerrain(&terrain, player_stalk_vec * 0.03f, VCAP); 
      */

      // Swap the screen buffers
      glfwSwapBuffers(window);
      current_frame = glfwGetTime();
      dt = (current_frame - last_frame);
      last_frame = current_frame;
		
      player.Update(dt);
      chunk1.Update(dt);
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

  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    player.GetPhysicalObj()->jump();//velocity.y = 10.0f;
  }

  if (key == GLFW_KEY_P && action == GLFW_PRESS) {
    //    player.PickupItem(&hammah);
  }
}
