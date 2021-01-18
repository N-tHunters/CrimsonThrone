#ifndef VECTORS_H
#define VECTORS_H

#include <glm/glm.hpp>

glm::vec2 normalize(glm::vec2);
glm::vec3 normalize(glm::vec3);
glm::vec3 get_normal(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);

#endif