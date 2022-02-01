#include <math.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <map>
#include <thread>
#include <future>
#ifdef _WIN32
#include <windows.h>
#endif

// GLEW
#include <GL/glew.h>

// GLFW
#define GLFW_INCLUDE_NONE
#define GLFW_DLL
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
#include <render/textures.hpp>
#include <render/models.hpp>
#include <render/shaders.hpp>

#include <physics/physicalObj.hpp>
#include <physics/boundary.hpp>
#include <physics/terrain.hpp>

#include <base/actors/player.hpp>
#include <base/actors/npc.hpp>
#include <base/items/item.hpp>
#include <base/location/chunk.hpp>
#include <base/location/location.hpp>
#include <base/triggers/shortjumptrigger.hpp>
#include <base/mouse_picker.hpp>
#include <base/items/weapon.hpp>

#include <magic/core.h>
#include <magic/symbols.h>

#include <sound/soundengine.h>
#include <sound/filesound.h>
#include <sound/voice.h>

#include <UI/frame.hpp>
#include <UI/bar.hpp>
#include <UI/text.hpp>
#include <UI/button.hpp>
#include <UI/textBox.hpp>
#include <UI/text3d.hpp>
#include <UI/image3d.hpp>
#include <UI/inventory.hpp>
#include <UI/dialogui.hpp>
#include <UI/mainmenu.hpp>

#include <landscape/dungeona1generator3d.hpp>

#include <base/configuration.hpp>
#include <base/location/worldmap.hpp>

#define NO_SOUND

const char CONFIG_FILE[] = "resources/settings.ini";

// Function prototypes
void key_callback(
  GLFWwindow* window,
  int key,
  int scancode,
  int action,
  int mode);

void mouse_button_callback(
  GLFWwindow* window,
  int button,
  int action,
  int mods);

void MessageCallback(
  GLenum source,
  GLenum type,
  GLuint id,
  GLenum severity,
  GLsizei length,
  const GLchar* message,
  const void* userParam);

// Global variabels

float VCAP = 0.1f;
Camera* camera;
Player* player;
SoundEngine sound_engine;
MagicCore * player_core;

Location * location;

int direction = 1;
float directionSide = 0;
float velocity = 5.0f;
bool player_wants_to_jump = false;
bool isRunning = false;
bool openedInventory = false;
bool inDialog = false;


bool push = false;
bool pressed_e = false;
float push_m = 0.0f;
void load_characters();
bool clicked;

;
int width, height;

TextBox* logs;
MousePicker* mouse_picker;

Inventory* inventory;

typedef void (*function)();

enum {
  STATE_LOADING,
  STATE_RUNNING,
  STATE_PAUSED,
  STATE_MAIN_MENU,
  STATE_CLOSING
} game_state;

GLFWwindow* window;

void change_to_running() {
  game_state = STATE_RUNNING;
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void change_to_main_menu() {
  game_state = STATE_MAIN_MENU;
  camera->setPosition(glm::vec3(0.0));
  camera->setRotation(glm::vec3(0.0));
}

void close_window() {
  game_state = STATE_CLOSING;
}

void loading_screen() {}

void loading() {
  init_demo_locations();
  game_state = STATE_MAIN_MENU;
}

int main() {
  clicked = false;
  game_state = STATE_LOADING;

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
  FileSound sound(&sound_engine, &source, "resources/sounds/firetail.wav");
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
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  window = glfwCreateWindow(
    mode->width,
    mode->height,
    "Crimson Throne",
    glfwGetPrimaryMonitor(),
    nullptr);

  glfwMakeContextCurrent(window);

#ifdef _WIN32
  // Turn on vertical screen sync under Windows.
  // (I.e. it uses the WGL_EXT_swap_control extension)
  typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXTPROC)(int interval);
  PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
  wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress(
    "wglSwapIntervalEXT");

  if (wglSwapIntervalEXT) {
    wglSwapIntervalEXT(0);
  }
#endif

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_NOTEQUAL, 0.0);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEBUG_OUTPUT);
  // glEnable(GL_CULL_FACE);
  // glEnable(GL_BACK);

  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);

  // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
  glewExperimental = GL_TRUE;
  // Initialize GLEW to setup the OpenGL Function pointers
  glewInit();

  //  glfwGetWindowSize(window, &width, &height);
  width = mode->width;
  height = mode->height;
  printf("Windows size is %ix%i\n", width, height);
  // Define the viewport dimensions
  glViewport(0, 0, width, height);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  glDebugMessageCallback(MessageCallback, 0);

  load_shaders(width, height);
  load_characters();

  // Initialize game objects
  init_models();

  camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  player = new Player("player",
            10,
            new PhysicalObj(glm::vec3(20.0f, 10.0f, 20.0f),
                    new BoundaryBox(glm::vec3(-0.2f, -0.5f, -0.2f), glm::vec3(0.2f, 0.5f, 0.2f))),
		      camera);
  player_core = new MagicCore();
  player_core->SetPhysicalObj(player->GetPhysicalObj());


  
  Image* image_loading = new Image(glm::vec4(width / 2 - 256, height / 2 - 256, 512, 512), "resources/textures/starting.png");
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glfwPollEvents();

  image_loading->draw();

  glFinish();

  glfwSwapBuffers(window);

  loading();

  while (game_state == STATE_LOADING) {
  }

  // ----------------------------------------------- CODE ------------------------------------------

  Text* fps_counter = new Text(std::to_string(0.0f),
    1.0f,
    glm::vec3(1.0f),
    glm::vec2(10, height - 100));

  float last_frame = glfwGetTime();
  int hp = player->GetHealth();
  int maxHp = player->GetMaxHealth();

  player->GetPhysicalObj()->name = "Player";

  Bar test_frame(glm::vec4(100, 100, 100, 10), &hp, &maxHp, glm::vec3(255.0, 0, 0));

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

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  glfwSetCursorPos(window, (double)width / 2.0, (double)height / 2.0);

  MainMenu main_menu = MainMenu((function)change_to_running, (function)close_window);

  game_state = STATE_MAIN_MENU;

  float dt = 0.0f;

  logs = new TextBox(glm::vec4(-0.9, -0.9, 1.8, 0.3),  20.0f, glm::vec3(255));

  DialogUI* current_dialog_ui = nullptr;
  inventory = new Inventory(*player);

  glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

  mouse_picker = new MousePicker(camera, projection_matrix);
  
  load_textures({"house"});

  Model* hammer_model = new Model("resources/models/hammah.obj");
  Mesh* hammer_mesh = new Mesh(hammer_model, get_texture("house"));
  PhysicalObj* hammer = new PhysicalObj(
    hammer_mesh,
    false, true, false, false,
    glm::vec3(10.0f, 10.0f, 10.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    "hammer",
    hammer_model->getBoundaryBox());

  Text* press_e_text = new Text(
    "Press [E]",
    0.4f,
    glm::vec3(0),
    glm::vec2(width / 2.0f, width / 2.0f));

  while (game_state != STATE_CLOSING) {
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

    float current_frame;
    float lastXPos = xpos;
    float lastYPos = ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (game_state == STATE_MAIN_MENU) {
      ypos = height - ypos;
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glfwPollEvents();

      main_menu.highlight(xpos, ypos);

      main_menu.draw();

      if (clicked) {
        main_menu.click(xpos, ypos);
      }

      // if (play_button->check(glm::vec2(xpos, ypos))) {
      //   play_button->update(glm::vec3(100));
      // } else {
      //   play_button->update(glm::vec3(0));
      // }

      // if (exit_button->check(glm::vec2(xpos, ypos))) {
      //   exit_button->update(glm::vec3(100));
      // } else {
      //   exit_button->update(glm::vec3(0));
      // }

      // if (clicked) {
        // play_button->click(glm::vec2(xpos, ypos));
        // exit_button->click(glm::vec2(xpos, ypos));
      // }

      // play_button->draw();
      // exit_button->draw();

      glFinish();

      glfwSwapBuffers(window);
      last_frame = glfwGetTime();
    } else {
      glm::vec2 cursorMotion = glm::vec2(lastXPos - xpos, lastYPos - ypos);
      if (game_state != STATE_PAUSED && !openedInventory) {
        if (cursorMotion.x != 0 || cursorMotion.y != 0) {
          if (player->GetSpeed().x != 0 || player->GetSpeed().y != 0) {
            player->CalculateSpeed(camera->getRotationY());
          }
          if (player->GetSideSpeed().x != 0 || player->GetSideSpeed().y != 0) {
            player->CalculateSideSpeed(camera->getRotationY());
          }
          cursorMotion *= sensivity;
          if (!inDialog) {
            player->GetCamera()->changeRotationX(-cursorMotion.y);
            player->GetCamera()->changeRotationY(-cursorMotion.x);
          }
          if (player->GetCamera()->getRotation().x < -90.0f)
            player->GetCamera()->setRotationX(-90.0f);
          if (player->GetCamera()->getRotation().x > 90.0f)
            player->GetCamera()->setRotationX(90.0f);
        }
      }

      glfwPollEvents();

      if (game_state == STATE_PAUSED) {
        ypos = height - ypos;
        // if (resume_button->check(glm::vec2(xpos, ypos))) {
          // resume_button->update(glm::vec3(255, 255, 0));
        // } else {
          // resume_button->update(glm::vec3(0));
        // }
        // if (exit_to_menu->check(glm::vec2(xpos, ypos))) {
          // exit_to_menu->update(glm::vec3(255, 255, 0));
        // } else {
          // exit_to_menu->update(glm::vec3(0));
        // }
        if (clicked) {
          // resume_button->click(glm::vec2(xpos, ypos));
          // exit_to_menu->click(glm::vec2(xpos, ypos));
        }
      }
      glEnable(GL_DEPTH_TEST);

      glClearColor(0.5f, 0.7f, 0.7f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      if (game_state != STATE_PAUSED) {
        GetCurrentLocation()->UpdatePosition(
          player->GetPhysicalObj()->getPosition());

        Chunk * chunk_ptr = GetCurrentLocation()->GetCurrentChunk();

        if (chunk_ptr == nullptr)
          chunk_ptr = GetCurrentLocation()->GetChunkByPosition(0, 0);
        while (!chunk_ptr->IsLoaded())
          GetCurrentLocation()->LoadABS();

        if (player_wants_to_jump && !inDialog) {
          if (GetMultijump())
            player->GetPhysicalObj()->jumpAnyway(chunk_ptr);
          else
            player->GetPhysicalObj()->jump(chunk_ptr);
        }



        if (!inDialog) {
          if (isRunning)
            player->GetPhysicalObj()->setSpeed(
              (player->GetSpeed() + player->GetSideSpeed()) * 30.0f);
          else
            player->GetPhysicalObj()->setSpeed(
              player->GetSpeed() + player->GetSideSpeed());
        }

        chunk_ptr->CheckAllTriggersAsPlayer(player->GetPhysicalObj());

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
        player->GetPhysicalObj()->collideTerrain(
          chunk_ptr->GetTerrain(),
          dt,
          chunk_ptr);
      }

      GetCurrentLocation()->Draw(camera, player);

      logs->draw();

      fps_counter->draw();

      if (openedInventory) {
        inventory->draw();
        inventory->update(dt);
      }

      mouse_picker->update();
      std::pair<Item *, float> result;
      result = GetCurrentLocation()->CollideItemsWithRay(
        player->GetPhysicalObj()->getPosition(),
        mouse_picker->getCurrentRay());
      Item * picked_item = result.first;
      if (picked_item != nullptr) {
        press_e_text->draw();
        if (pressed_e) {
          player->PickupItem(picked_item);
          GetCurrentLocation()->GetCurrentChunk()->DeleteItem(picked_item);
        }
      }

      std::pair<Actor*, float> collided_actors;
      collided_actors = GetCurrentLocation()->CollideActorsWithRay(
        player->GetPhysicalObj()->getPosition(),
        mouse_picker->getCurrentRay());
      Actor* collided_actor = collided_actors.first;

      if (collided_actor != nullptr) {
        if (clicked && !inDialog) {
          Weapon* player_weapon = player->GetWeapon();
          float weapon_range = 3.0f;
          if (player_weapon != nullptr) {
            weapon_range = player_weapon->GetRange();
          }
          if (weapon_range > collided_actors.second) {
            int player_damage = player->GetDamage();
            collided_actor->DealDamage(player_damage);
          }
        } else if (pressed_e) {
          inDialog = true;
          reinterpret_cast<NPC*>(collided_actor)->getDialog()->startDialog(player);
          current_dialog_ui = new DialogUI(
            reinterpret_cast<NPC*>(collided_actor),
            width,
            height);
          glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
      }

      if (game_state == STATE_PAUSED) {
        // resume_button->draw();
        // exit_to_menu->draw();
      } else if (game_state == STATE_RUNNING) {
        if (current_dialog_ui != nullptr) {
          current_dialog_ui->draw();
          if (clicked) {
            if (current_dialog_ui->click(xpos, height - ypos)) {
              current_dialog_ui = nullptr;
              glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
              inDialog = false;
            }
          }
        }
      }

      glFinish();

      glfwSwapBuffers(window);

      if (game_state != STATE_PAUSED) {
        player_core->Step();
        GetCurrentLocation()->Update(dt);
        current_frame = glfwGetTime();
        dt = std::min((current_frame - last_frame), 0.1f);
        last_frame = current_frame;

        if (glfwGetTime() - fps_change_last > 0.1) {
          fps_counter->update(
            std::to_string(static_cast<int>(round(1.0 / dt))));
          fps_change_last = glfwGetTime();
        }
      } else {
        last_frame = glfwGetTime();
      }

      if (glfwWindowShouldClose(window)) {
        game_state = STATE_PAUSED;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetWindowShouldClose(window, GL_FALSE);
      }
    }

    player_wants_to_jump = false;
    push = false;
    clicked = false;
    pressed_e = false;
  }
  glfwTerminate();
  return 0;
}

void mouse_button_callback(
  GLFWwindow* window,
  int button,
  int action,
  int mods) {
  if (action == GLFW_PRESS) {
    clicked = true;
  }
}

void key_callback(
  GLFWwindow* window,
  int key,
  int scancode,
  int action,
  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    if (game_state == STATE_RUNNING) {
      if (openedInventory) {
        openedInventory = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      } else {
      game_state = STATE_PAUSED;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      }
    } else if (game_state == STATE_PAUSED) {
      game_state = STATE_RUNNING;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
  }
  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    if (openedInventory) {
    } else {
      player->SetDirection(1.0f);
    player->CalculateSpeed(player->GetCamera()->getRotation().y);
    }
  }
  if (key == GLFW_KEY_W &&
      action == GLFW_RELEASE &&
      player->GetDirection() > 0) {
    if (openedInventory) {
      inventory->prevElement();
    } else {
      player->SetSpeed(glm::vec2(0.0f));
    }
  }
  if (key == GLFW_KEY_S && action == GLFW_PRESS) {
    if (openedInventory) {
      inventory->nextElement();
    } else {
      player->SetDirection(-1.0f);
      player->CalculateSpeed(player->GetCamera()->getRotation().y);
    }
  }
  if (key == GLFW_KEY_S &&
      action == GLFW_RELEASE &&
      player->GetDirection() < 0) {
    if (openedInventory) {
    } else {
    player->SetSpeed(glm::vec2(0.0f));
    }
  }
  if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    if (openedInventory) {
    } else {
      player->SetSideDirection(-1.0f);
    player->CalculateSideSpeed(player->GetCamera()->getRotation().y);
    }
  }
  if (key == GLFW_KEY_A &&
      action == GLFW_RELEASE &&
      player->GetSideDirection() < 0.0f) {
    if (openedInventory) {
    } else {
    player->SetSideSpeed(glm::vec2(0.0f));
    }
  }

  if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    if (openedInventory) {
    } else {
      player->SetSideDirection(1.0f);
    player->CalculateSideSpeed(player->GetCamera()->getRotation().y);
    }
  }

  if (key == GLFW_KEY_D &&
      action == GLFW_RELEASE &&
      player->GetSideDirection() > 0.0f) {
    if (openedInventory) {
    } else {
    player->SetSideSpeed(glm::vec2(0.0f));
    }
  }

  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    if (openedInventory) {
      inventory->selectElement();
    } else {
      player_wants_to_jump = true;
    }
  }

  if (key == GLFW_KEY_E) {
    pressed_e = true;
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

  if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
    isRunning = true;
  }

  if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
    isRunning = false;
  }

  if (key == GLFW_KEY_I && action == GLFW_RELEASE) {
    openedInventory = !openedInventory;
    if (openedInventory) {
      inventory->open();
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
  }
}

void MessageCallback(
  GLenum source,
  GLenum type,
  GLuint id,
  GLenum severity,
  GLsizei length,
  const GLchar* message,
  const void* userParam) {
  // fprintf(
  //   stderr,
  //   "GL ERROR: source = 0x%x,\
  //   type = 0x%x,\
  //   id = 0x%x, severity = 0x%x, message = %s\n",
  //   source,
  //   type,
  //   id,
  //   severity,
  //   message);
}
