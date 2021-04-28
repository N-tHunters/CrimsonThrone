#include "landscapegenerator.hpp"

LandscapeGenerator::LandscapeGenerator() {}
void LandscapeGenerator::Generate(Location *, size_t, size_t, int, int, int) {}


PhysicalObj * create_wall(glm::vec3 position, glm::vec3 size, std::string texture_path) {
  std::vector<float> vertices;
  std::vector<unsigned int> indices;

  glm::vec3 halfs = size * 0.5f;

  glm::vec3 v[8] = {
			      glm::vec3(-halfs.x, -halfs.y, -halfs.z),
			      glm::vec3(halfs.x, -halfs.y, -halfs.z),
			      glm::vec3(-halfs.x, halfs.y, -halfs.z),
			      glm::vec3(halfs.x, halfs.y, -halfs.z),
			      glm::vec3(-halfs.x, -halfs.y, halfs.z),
			      glm::vec3(halfs.x, -halfs.y, halfs.z),
			      glm::vec3(-halfs.x, halfs.y, halfs.z),
			      glm::vec3(halfs.x, halfs.y, halfs.z)
  };

  /*glm::vec3 v[8] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(size.x, 0.0, 0.0),
            glm::vec3(0.0, size.y, 0.0),
            glm::vec3(size.x, size.y, 0.0),
            glm::vec3(0.0, 0.0, size.z),
            glm::vec3(size.x, 0.0, size.z),
            glm::vec3(0.0, size.y, size.z),
            glm::vec3(size.x, size.y, size.z)
  };*/

  // z * y

  push_vertex(&vertices, v[0], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
  push_vertex(&vertices, v[1], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, 0.0f));
  push_vertex(&vertices, v[2], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, size.y * 0.5));
  push_vertex(&vertices, v[3], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, size.y * 0.5));
  push_vertex(&vertices, v[2], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, size.y * 0.5));
  push_vertex(&vertices, v[1], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, 0.0f));

  // z * y

  push_vertex(&vertices, v[4], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, 0.0f));
  push_vertex(&vertices, v[5], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
  push_vertex(&vertices, v[6], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, size.y * 0.5));
  push_vertex(&vertices, v[5], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
  push_vertex(&vertices, v[7], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, size.y * 0.5));
  push_vertex(&vertices, v[6], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, size.y * 0.5));

  // x * y

  push_vertex(&vertices, v[0], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
  push_vertex(&vertices, v[2], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, size.y * 0.5));
  push_vertex(&vertices, v[6], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.z * 0.5, size.y * 0.5));
  push_vertex(&vertices, v[0], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
  push_vertex(&vertices, v[4], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.z * 0.5, 0.0f));
  push_vertex(&vertices, v[6], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.z * 0.5, size.y * 0.5));

  // x * y

  push_vertex(&vertices, v[3], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.z * 0.5, size.y * 0.5));
  push_vertex(&vertices, v[7], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, size.y * 0.5));
  push_vertex(&vertices, v[5], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
  push_vertex(&vertices, v[3], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.z * 0.5, size.y * 0.5));
  push_vertex(&vertices, v[1], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.z * 0.5, 0.0f));
  push_vertex(&vertices, v[5], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));

  // z * x, bottom

  push_vertex(&vertices, v[0], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
  push_vertex(&vertices, v[1], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, 0.0f));
  push_vertex(&vertices, v[4], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, size.z * 0.5));
  push_vertex(&vertices, v[5], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, size.z * 0.5));
  push_vertex(&vertices, v[1], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, 0.0f));
  push_vertex(&vertices, v[4], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, size.z * 0.5));

  // z * x, top

  push_vertex(&vertices, v[2], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f));
  push_vertex(&vertices, v[3], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, 0.0f));
  push_vertex(&vertices, v[6], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, size.z * 0.5));
  push_vertex(&vertices, v[7], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, size.z * 0.5));
  push_vertex(&vertices, v[3], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(size.x * 0.5, 0.0f));
  push_vertex(&vertices, v[6], glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, size.z * 0.5));

  for(int i = 0; i < 3 * 2 * 6; i++)
    indices.push_back(i);

  
  return new PhysicalObj(new Mesh(texture_path, &vertices, &indices),
			 false,
       true,
       false,
       false,
       position,
       glm::vec3(0.0f, 0.0f, 0.0f),
       "wall",
       new BoundaryBox(-size * 0.5f, size * 0.5f));
}
