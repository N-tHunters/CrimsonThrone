#include <render/shaders.hpp>

Shader shader3D;
Shader shaderGUI;
Shader shaderText;
Shader shaderWater;
Shader shaderPost;
Shader shaderText3D;
Shader shaderParticle;
glm::vec2 screen_resolution;

void load_shaders(int width, int height) {
  shader3D = Shader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");
  shaderGUI = Shader("resources/shaders/GUI_vertex_shader.glsl", "resources/shaders/GUI_fragment_shader.glsl");
  shaderText = Shader("resources/shaders/GUI_vertex_shader.glsl", "resources/shaders/text_fragment_shader.glsl");
  shaderWater = Shader("resources/shaders/water_vertex_shader.glsl", "resources/shaders/water_fragment_shader.glsl");
  shaderPost = Shader("resources/shaders/post_vertex_shader.glsl", "resources/shaders/post_fragment_shader.glsl");
  shaderText3D = Shader("resources/shaders/text3d_vertex_shader.glsl", "resources/shaders/text3d_fragment_shader.glsl");
  shaderParticle = Shader("resources/shaders/particle_vertex_shader.glsl", "resources/shaders/particle_fragment_shader.glsl");
  screen_resolution = glm::vec2(width, height);
}